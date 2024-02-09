//
//  main.cpp
//  my_workspace
//
//  Created by Arthur on 09.02.24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec) {
    for(const T& data: vec) {
        os << data;
    }
    return os;
}

void printWavFile(const std::string&);
void copyWavFile(const std::string&, const std::string&);
void reverseAudio(const std::string&, const std::string&);
int main(int argc, const char * argv[]) {
    const std::string wavfile = "/Users/arthur/Desktop/sample.wav";
//    printWavFile(wavfile);
    const std::string wavfile2 = "/Users/arthur/Desktop/output.wav";
    copyWavFile(wavfile,wavfile2);
    reverseAudio(wavfile, wavfile2);
}

void printWavFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    // Read the WAV header (first 44 bytes, the header)
    const int headerSize = 44;
    std::vector<char> headerData(headerSize);
    file.read(headerData.data(), headerSize);

    // Read the rest of the file (audio data)
    std::vector<char> audioData(std::istreambuf_iterator<char>(file), {});

    file.close();

    std::cout << "Header : " << headerData << " bytes" << std::endl;
    std::cout << "Audio data : " << audioData << " bytes" << std::endl;
}
void copyWavFile(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream ifile(inputFileName);
    std::ofstream ofile(outputFileName);
    if(!ifile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }
    if(!ofile.is_open()) {
        ifile.close();
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }
    
    char byte;
    while(ifile.get(byte)){
        ofile << byte;
    }
    
    ifile.close();
    ofile.close();
}

struct WavHeader {
    char ChunkID[4];
    uint32_t ChunkSize;
    char Format[4];
    char Subchunk1ID[4];
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    char Subchunk2ID[4];
    uint32_t Subchunk2Size; //audio data size
};
template <typename T>
void reverseAudioSamples(std::vector<T>& audioData) {
    std::reverse(audioData.begin(), audioData.end());
}
void reverseAudio(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream ifile(inputFileName, std::ios::binary);
    if (!ifile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFileName << std::endl;
        return;
    }

    const int headerSize = 44;
    WavHeader header;
    ifile.read(reinterpret_cast<char*>(&header), headerSize);


    std::vector<char> audioData(header.Subchunk2Size);
    ifile.read(reinterpret_cast<char*>(audioData.data()), header.Subchunk2Size);

    switch (header.BitsPerSample) {
        case 8:
            reverseAudioSamples(reinterpret_cast<std::vector<int8_t>&>(audioData));
            break;
        case 16:
            reverseAudioSamples(reinterpret_cast<std::vector<int16_t>&>(audioData));
            break;
        case 32:
            reverseAudioSamples(reinterpret_cast<std::vector<int32_t>&>(audioData));
            break;
        default:
            std::cerr << "Unsupported sample size: " << header.BitsPerSample << std::endl;
            return;
    }


    std::ofstream ofile(outputFileName, std::ios::binary);
    if (!ofile.is_open()) {
        ifile.close();
        std::cerr << "Failed to open output file: " << outputFileName << std::endl;
        return;
    }
    
    ofile.write(reinterpret_cast<char*>(&header), headerSize);
    ofile.write(reinterpret_cast<char*>(audioData.data()), header.Subchunk2Size);
    
    ifile.close();
    ofile.close();
}
