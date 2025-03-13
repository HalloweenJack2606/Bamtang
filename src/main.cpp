#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

typedef uint32_t uint32;

std::string decryptMessage(const std::string& message, const std::string& freqLang)
{
    std::unordered_map<char, uint32> frequencyMap;

    for(const char& c : message)
    {
        if(isalpha(c))
        {
            frequencyMap[std::toupper(c)]++;
        }
    }

    std::vector<std::pair<char, uint32>> frequencyPair(std::begin(frequencyMap), std::end(frequencyMap));
    std::sort(std::begin(frequencyPair), std::end(frequencyPair), [](auto& lhs, auto& rhs) {
        return lhs.second > rhs.second;
    });

    std::unordered_map<char, char> substitutionMap;
    for(int i = 0; i < frequencyPair.size(); i++)
    {
        const char oldChar = frequencyPair[i].first;
        const char newChar = freqLang[i];
        substitutionMap[oldChar] = newChar;
        substitutionMap[std::tolower(oldChar)] = std::tolower(newChar);
    }

    std::string decrypted = message;
    for(auto& c : decrypted)
    {
        if(substitutionMap.count(c))
        {
            c = substitutionMap[c];
        }
    }
    return decrypted;
}


int main()
{
    const std::string message = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\n"
                                "Xof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\n"
                                "Zgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\n"
                                "Xof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\n"
                                "(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\n"
                                "(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";
    const std::string freqLang = "TEOAISRHNUCMDLGWFPYKJBVQX";

    const std::string decrypted = decryptMessage(message, freqLang);

    std::cout << decrypted << std::endl;

    std::cin.get();
    return 0;
}
