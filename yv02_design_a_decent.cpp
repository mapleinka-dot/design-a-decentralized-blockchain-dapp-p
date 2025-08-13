// yv02_design_a_decent.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

// Blockchain structure
struct Block {
    int id;
    std::string hash;
    std::string previousHash;
    std::vector<std::string> transactions;
};

// dApp structure
struct dApp {
    std::string name;
    std::string description;
    std::vector<std::string> functions;
};

// dApp Parser class
class dAppParser {
private:
    std::map<std::string, dApp> dAppRegistry;
    std::vector<Block> blockchain;

public:
    // Add a new dApp to the registry
    void addDApp(const std::string& name, const std::string& description, const std::vector<std::string>& functions) {
        dApp newDApp = {name, description, functions};
        dAppRegistry[name] = newDApp;
    }

    // Add a new block to the blockchain
    void addBlock(const Block& block) {
        blockchain.push_back(block);
    }

    // Parse a dApp from a block's transaction data
    dApp parseDApp(const std::string& transactionData) {
        // Tokenize the transaction data
        std::vector<std::string> tokens = tokenize(transactionData);

        // Extract the dApp name and function names
        std::string dAppName = tokens[0];
        std::vector<std::string> functionNames;
        for (int i = 1; i < tokens.size(); i++) {
            functionNames.push_back(tokens[i]);
        }

        // Check if the dApp is in the registry
        if (dAppRegistry.find(dAppName) != dAppRegistry.end()) {
            dApp parsedDApp = dAppRegistry[dAppName];
            parsedDApp.functions = functionNames;
            return parsedDApp;
        } else {
            // If not, create a new dApp and add it to the registry
            dApp newDApp = {dAppName, "Parsed from blockchain", functionNames};
            dAppRegistry[dAppName] = newDApp;
            return newDApp;
        }
    }

    // Tokenize a string into a vector of substrings
    std::vector<std::string> tokenize(const std::string& str) {
        std::vector<std::string> tokens;
        std::string token;
        for (char c : str) {
            if (c == ' ') {
                if (!token.empty()) {
                    tokens.push_back(token);
                    token.clear();
                }
            } else {
                token += c;
            }
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

int main() {
    dAppParser parser;

    // Add some sample dApps to the registry
    parser.addDApp("MyDApp", "My decentralized application", {"func1", "func2"});
    parser.addDApp("YourDApp", "Your decentralized application", {"func3", "func4"});

    // Create some sample blocks
    Block block1 = {1, "block1hash", "", {"MyDApp func1 10", "MyDApp func2 20"}};
    Block block2 = {2, "block2hash", "block1hash", {"YourDApp func3 30", "YourDApp func4 40"}};

    // Add the blocks to the blockchain
    parser.addBlock(block1);
    parser.addBlock(block2);

    // Parse the dApps from the blockchain transactions
    for (const Block& block : parser.blockchain) {
        for (const std::string& transaction : block.transactions) {
            dApp parsedDApp = parser.parseDApp(transaction);
            std::cout << "Parsed dApp: " << parsedDApp.name << " - " << parsedDApp.description << std::endl;
            std::cout << "Functions:" << std::endl;
            for (const std::string& func : parsedDApp.functions) {
                std::cout << "  " << func << std::endl;
            }
            std::cout << std::endl;
        }
    }

    return 0;
}