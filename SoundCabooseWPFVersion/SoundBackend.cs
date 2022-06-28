using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using Syncfusion;
using Syncfusion.Windows.Tools.Controls;
using Syncfusion.SfSkinManager;
using Syncfusion.Windows.PropertyGrid;
using SoundCabooseWPFVersion.code;
using SoundCabooseWPFVersion.CustomControls;
using NAudio;
using NAudio.Wave;
using NAudio.Utils;
using NAudio.Wave.SampleProviders;
using System.Threading;

namespace SoundCabooseWPFVersion.code
{
    public class SoundBackend
    {


        public abstract class WaveProvider32 : IWaveProvider
        {
            private WaveFormat waveFormat;

            public WaveProvider32()
                : this(44100, 1)
            {
            }

            public WaveProvider32(int sampleRate, int channels)
            {
                SetWaveFormat(sampleRate, channels);
            }

            public void SetWaveFormat(int sampleRate, int channels)
            {
                this.waveFormat = WaveFormat.CreateIeeeFloatWaveFormat(sampleRate, channels);
            }

            public int Read(byte[] buffer, int offset, int count)
            {
                WaveBuffer waveBuffer = new WaveBuffer(buffer);
                int samplesRequired = count / 4;
                int samplesRead = Read(waveBuffer.FloatBuffer, offset / 4, samplesRequired);
                return samplesRead * 4;
            }

            public abstract int Read(float[] buffer, int offset, int sampleCount);

            public WaveFormat WaveFormat
            {
                get { return waveFormat; }
            }
        }

        public class SineWaveProvider32 : WaveProvider32
        {
            int sample;

            public SineWaveProvider32()
            {
                Frequency = 1000;
                Amplitude = 0.25f; // let's not hurt our ears
            }

            public float Frequency { get; set; }
            public float Amplitude { get; set; }

            public override int Read(float[] buffer, int offset, int sampleCount)
            {
                int sampleRate = WaveFormat.SampleRate;
                for (int n = 0; n < sampleCount; n++)
                {
                    buffer[n + offset] = (float)(Amplitude * Math.Sin((2 * Math.PI * sample * Frequency) / sampleRate));
                    sample++;
                    if (sample >= sampleRate) sample = 0;
                }
                return sampleCount;
            }
        }

        private WaveOut waveOut;

        private void StartStopSineWave()
        {
            if (waveOut == null)
            {
                var sineWaveProvider = new SineWaveProvider32();
                sineWaveProvider.SetWaveFormat(16000, 1); // 16kHz mono
                sineWaveProvider.Frequency = 1000;
                sineWaveProvider.Amplitude = 0.25f;
                waveOut = new WaveOut();
                waveOut.Init(sineWaveProvider);
                waveOut.Play();
            }
            else
            {
                waveOut.Stop();
                waveOut.Dispose();
                waveOut = null;
            }
        }
    }
}
