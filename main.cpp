#include <iostream>
#include <fstream>
#include <string>
#include <jwt-cpp/jwt.h>
#include <unistd.h>

/**
 * Argument 1: JWT
 * Argument 2: Issuer
 * Argument 3: [OPTIONAL] PRIVATE KEY or FILE with PRIVATE KEY
 *             Private key: Very long string
 *             File: file:<path>
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {

    if (argc < 3 || argc > 4) {
        std::cerr << "Argument(s) missing\n";
        std::cout << "First must be the Issuer url.\n"
                     "Second must be the JWT token.\n"
                     "Optional third is the private Key.\n"
                     "- This can be a string with the key or a path.\n"
                     "- Key: First char of string is not '/' or '~'\n"
                     "- If not defined, then must be a file 'jwt.key' placed in the home root.\n";
        return 1;
    }

    std::string path{argv[0]};
    std::string issuer{argv[1]};
    std::string jwt{argv[2]};
    std::string privKey{argc == 4 ? argv[3] : "~/jwt.key"};

    try {

        auto validator = jwt::verify();
        validator.with_issuer(issuer);

        if (privKey.find('/') == 0 || privKey.find('~') == 0) {
            /**
             * Get the private key from file
             */

            if (privKey.find('~') == 0) {
                privKey = std::string{std::getenv("HOME")} + privKey.substr(1);
            }

            if (access(privKey.c_str(), F_OK) == -1) {
                throw std::runtime_error("Private key file '" + privKey + "' not found\n");
            }

            std::ifstream fh{privKey.c_str()};

            std::string privateKey((std::istreambuf_iterator<char>(fh)),
                                   std::istreambuf_iterator<char>());

            validator.allow_algorithm(jwt::algorithm::rs256("", privateKey));

        } else {
            /**
             * The private key as argument
             */

            if (privKey.find("-----BEGIN RSA PRIVATE KEY-----") == std::string::npos) {
                privKey = "-----BEGIN RSA PRIVATE KEY-----\n" + privKey + "\n-----END RSA PRIVATE KEY-----";
            }

            validator.allow_algorithm(jwt::algorithm::rs256("", privKey));

        }

        auto tokenParsed = jwt::decode(jwt);
        validator.verify(tokenParsed);

    } catch (const std::exception &ex) {

        std::cerr << ex.what() << "\n";
        return 1;

    }

    return 0;
}
