#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct WAV_HEADER{
    // Riff
    uint8_t chunkID[4];
    uint32_t chunkSize;
    uint8_t format[4];
    // FMT
    uint8_t subchunk1ID[4];
    uint32_t subchunk1Size;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
    // Data
    uint8_t subchunk2ID[4];
    uint32_t subchunk2Size;
};

class AudioReader{
    public:
    int sampleRateForAllChannels;
    int framecount=0;
    vector<int16_t> data;
    AudioReader(const std::string &file_path){
        this->data = getDataFromWav(file_path);
    }


    vector<int16_t> getDataFromWav(const std::string &file_path){
        ifstream wav(file_path);
        struct WAV_HEADER whr;
        if(!wav.is_open()){
            throw "File Could Not be Opened!";
        }
      
        // Riff
        wav.read((char*)&whr.chunkID, sizeof(whr.chunkID)); 
        wav.read((char*)&whr.chunkSize, sizeof(whr.chunkSize));
        wav.read((char*)&whr.format, sizeof(whr.format));

        // fmt
        wav.read((char*)&whr.subchunk1ID, sizeof(whr.subchunk1ID));
        wav.read((char*)&whr.subchunk1Size, sizeof(whr.subchunk1Size));
        wav.read((char*)&whr.audioFormat,sizeof(whr.audioFormat));
        wav.read((char*)&whr.numChannels,sizeof(whr.numChannels));
        wav.read((char*)&whr.sampleRate,sizeof(whr.sampleRate));
        wav.read((char*)&whr.byteRate,sizeof(whr.byteRate));
        wav.read((char*)&whr.blockAlign,sizeof(whr.blockAlign));
        wav.read((char*)&whr.bitsPerSample,sizeof(whr.bitsPerSample));

        // Data
        wav.read((char*)&whr.subchunk2ID,sizeof(whr.subchunk2ID));
        wav.read((char*)&whr.subchunk2Size,sizeof(whr.subchunk2Size));
        sampleRateForAllChannels = whr.numChannels*whr.sampleRate;
        framecount = whr.subchunk2Size * 8 /whr.bitsPerSample;
        /*cout<<"format "<< whr.format<<endl;
        cout << "sampleRate : " << whr.sampleRate<<endl;
        cout << "byteRate" << whr.byteRate<<endl;
        cout<< "subchunk2size " << whr.subchunk2Size << endl;
        cout<<"framecount "<<framecount<<endl;
        cout << "channels "<< whr.numChannels<<endl;
        cout << "bitsPerSample "<< whr.bitsPerSample<<endl;
*/
        framecount = (this->Get_Size(file_path) -44) * 8 /whr.bitsPerSample;
        //cout <<"framecount "<< framecount<<endl;
        vector<int16_t> data(framecount);
        for(int i = 0; i < framecount; i++){
            wav.read((char*)&data[i],sizeof(data[i]));
            //cout<<i<<" : "<<data[i]<<endl; 
        }
        // Read audio data
        wav.close();
        
        return data;
    }


    int Get_Size( string path )
{
// 
FILE *pFile = NULL;

// get the file stream
pFile = fopen(path.c_str(), "rb" );

// set the file pointer to end of file
fseek( pFile, 0, SEEK_END );

// get the file size
int Size = ftell( pFile );

// return the file pointer to begin of file if you want to read it
// rewind( pFile );

// close stream and release buffer
fclose( pFile );

return Size;
}
};



