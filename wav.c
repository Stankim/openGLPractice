
WavAnalysis wav_analyse;
    static const uint16_t BUFFER_SIZE = 1024;
    uint8_t* buffer = new uint8_t[BUFFER_SIZE];
    std::cout << "Buffering data... " << std::endl;
    fseek(wavFile, 44, SEEK_SET); // skip header data
    while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
    {
        //do sth with buffer data
        wav_analyse.FFT(buffer); // currently shows data only
    }