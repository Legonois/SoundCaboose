using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using static System.Math;
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
    public static class SoundBackend
    {

        //Frequency Hertz to Angular Velocity
        public static float av(float hertz)
        { 
            return hertz * 2 * (float)PI;
        }

        public enum WaveType
        {
            Sine,
            Sawtooth,
            Square,
            Triangle,
            Noise
        }

        public abstract class WaveProvider32 : IWaveProvider
        {
            private WaveFormat waveFormat;

            public float Frequency { get; set; }
            public float Amplitude { get; set; }

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

        //Sine Wave

        public class SineWaveProvider32 : WaveProvider32
        {
            int sample;

            public SineWaveProvider32()
            {
                Frequency = 1000;
                Amplitude = 0.25f; // let's not hurt our ears
            }

            

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

        //Square Wave

        public class SquareWaveProvider32 : WaveProvider32
        {

            int sample;

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

        //Triangle Wave

        public class TriangleWaveProvider32 : WaveProvider32
        {

            int sample;

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

        //Sawtooth Wave

        public class SawWaveProvider32 : WaveProvider32
        {

            int sample;

            public override int Read(float[] buffer, int offset, int sampleCount)
            {
                int sampleRate = WaveFormat.SampleRate;
                for (int n = 0; n < sampleCount; n++)
                {
                    //Sawtooth Wave Math
                    int passes = 40;
                    float[] sum;

                    sum = new float[40];

                    //Sumation
                    for (int sn = 1; sn < passes; sn++)
                    {
                        sum[sn] = (float)(-1 * (Sin(sn * av(Frequency) * PI * 2 * sample) / sn));
                    }

                    buffer[n + offset] = (float)(Amplitude * 2 / PI * sum.Sum() / sampleRate);
                    sample++;
                    if (sample >= sampleRate) sample = 0;
                }
                return sampleCount;
            }
        }

        //Noise Wave

        public class NoiseWaveProvider32 : WaveProvider32
        {

            int sample;

            public override int Read(float[] buffer, int offset, int sampleCount)
            {
                int sampleRate = WaveFormat.SampleRate;

                Random rand = new Random();

                for (int n = 0; n < sampleCount; n++)
                {
                    

                    buffer[n + offset] = (float)(Amplitude * rand.Next(0, 1) / sampleRate);
                    sample++;
                    if (sample >= sampleRate) sample = 0;
                }
                return sampleCount;
            }
        }

        private static WaveOut waveOut;

        public static void StartStopSineWave(float frequency, float amplitude, int samplerate, int channels, WaveType waveType)
        {


            WaveProvider32 waveProvider = null;

            switch (waveType)
            {
                default:

                    break;

                case WaveType.Sine:

                    waveProvider = new SineWaveProvider32();

                    break;

                case WaveType.Sawtooth:

                    waveProvider = new SawWaveProvider32();

                    break;

                case WaveType.Triangle:

                    waveProvider = new TriangleWaveProvider32();

                    break;

                case WaveType.Square:

                    waveProvider = new SquareWaveProvider32();

                    break;

                case WaveType.Noise:

                    waveProvider = new NoiseWaveProvider32();

                    break;
            }

            if (waveOut == null)
            {

                waveProvider.SetWaveFormat(samplerate, channels); // 16kHz mono
                waveProvider.Frequency = frequency;
                waveProvider.Amplitude = amplitude;
                waveOut = new WaveOut();
                waveOut.Init(waveProvider);
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
