#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

class Block {
public:
    std::string prevHash;
    std::string data;
    time_t timestamp;
    int nonce;
    std::string hash;

    Block(const std::string& data, const std::string& prevHash) 
        : data(data), prevHash(prevHash), timestamp(time(nullptr)), nonce(0) {
        hash = calculateHash();
    }

    std::string calculateHash() const {
        std::stringstream ss;
        ss << prevHash << data << timestamp << nonce;
        
        unsigned char digest[SHA256_DIGEST_LENGTH];
        SHA256((const unsigned char*)ss.str().c_str(), 
               ss.str().length(), 
               digest);
        
        std::stringstream hashStream;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            hashStream << std::hex << std::setw(2) << std::setfill('0') 
                      << (int)digest[i];
        }
        
        return hashStream.str();
    }

    void mineBlock(int difficulty) {
        std::string target(difficulty, '0');
        while (hash.substr(0, difficulty) != target) {
            nonce++;
            hash = calculateHash();
        }
    }
};

class Blockchain {
    std::vector<Block> chain;
    int difficulty;

public:
    Blockchain() : difficulty(4) {
        chain.emplace_back("Genesis Block", "0");
    }

    void addBlock(const std::string& data) {
        Block newBlock(data, chain.back().hash);
        newBlock.mineBlock(difficulty);
        chain.push_back(newBlock);
    }

    bool isValid() const {
        for (size_t i = 1; i < chain.size(); i++) {
            const Block& current = chain[i];
            const Block& previous = chain[i-1];
            
            if (current.hash != current.calculateHash()) return false;
            if (current.prevHash != previous.hash) return false;
        }
        return true;
    }
};
