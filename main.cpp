#include <iostream>
using namespace std;

class SHA256{
        private:
        int msgLength;  // In bit of binary
        int paddedLength;
        string h[8];
        // HASH VALUES

        void resetHashValue() {
                h[0] = "6a09e667";
                h[1] = "bb67ae85";
                h[2] = "3c6ef372";
                h[3] = "a54ff53a";
                h[4] = "510e527f";
                h[5] = "9b05688c";
                h[6] = "1f83d9ab";
                h[7] = "5be0cd19";

        }

        string k[64] = {
                "428a2f98","71374491","b5c0fbcf","e9b5dba5","3956c25b","59f111f1","923f82a4","ab1c5ed5",
                "d807aa98","12835b01","243185be","550c7dc3","72be5d74","80deb1fe","9bdc06a7","c19bf174",
                "e49b69c1","efbe4786","0fc19dc6","240ca1cc","2de92c6f","4a7484aa","5cb0a9dc","76f988da",
                "983e5152","a831c66d","b00327c8","bf597fc7","c6e00bf3","d5a79147","06ca6351","14292967",
                "27b70a85","2e1b2138","4d2c6dfc","53380d13","650a7354","766a0abb","81c2c92e","92722c85",
                "a2bfe8a1","a81a664b","c24b8b70","c76c51a3","d192e819","d6990624","f40e3585","106aa070",
                "19a4c116","1e376c08","2748774c","34b0bcb5","391c0cb3","4ed8aa4a","5b9cca4f","682e6ff3",
                "748f82ee","78a5636f","84c87814","8cc70208","90befffa","a4506ceb","bef9a3f7","c67178f2"
        };

        void getMsgLen(string l) {
                msgLength = l.size() * 8;
        }

        void getPadLen(string l) {
                int bits = msgLength;
                paddedLength = ((bits + 65) / 512 + 1) * 512;
                if (bits + 65 <= 512) paddedLength = 512;
        }

        string rightRotate(string l, int n) {
                string out = l.substr(32 - n, n) + l.substr(0, 32 - n);

                return out;
        }

        string rightShift(string l, int n) {
                string out = "";
                for (int i = 0; i < n; i++) out += '0';
                out = out + l.substr(0, 32 - n);

                return out;
        }

        string xOR(string l1, string l2) {
                string temp = "";
                for (int i = 0; i < l1.size(); i++) {
                        if ((l1[i] == '1' and l2[i] != '1') or (l1[i] != '1' and l2[i] == '1')) temp += '1';
                        else temp += '0';
                }

                return temp;
        }

        string NOT(string l) {
                string output = "";
                for (int i = 0; i < l.size(); i++) {
                        if (l[i] == '0') output += '1';
                        else output += '0';
                }

                return output;
        }

        string AND(string l1, string l2) {
                string output = "";
                for (int i = 0; i < l1.size(); i++) {
                        if (l1[i] == l2[i]) output += '1';
                        else output += '0';
                }

                return output;               
        }

        string sigma0(int i, string *w) {
                string a = w[i-15];  
                string b = w[i-15];  
                string c = w[i-15];  
                a = rightRotate(a,7);
                b = rightRotate(b,18);
                c = rightShift(c,3);
                return xOR(xOR(a,b),c);
        }

        string sigma1(int i, string *w) {
                string a = w[i-2];  
                string b = w[i-2];  
                string c = w[i-2];  
                a = rightRotate(a,17);
                b = rightRotate(b,19);
                c = rightShift(c,10);
                return xOR(xOR(a,b),c);
        }

        string addtion(string l1, string l2) {
                int carry = 0;
                string result = "";
            
                for (int i = l1.size() - 1; i >= 0; i--) {
                        int bit1 = l1[i] - '0';
                        int bit2 = l2[i] - '0';
                    
                        // Sum of bits plus carry
                        int sum = bit1 + bit2 + carry;
                    
                        // Current bit and new carry
                        result = to_string(sum % 2) + result;
                        carry = sum / 2;
                }
            
                        // Add remaining carry if exists
                if (carry) {
                        result = "1" + result;
                }

                if (result.size() > 32) {
                        result = result.substr(result.size() - 32);
                }
            
                return result;
        }
        string toBin(int num) {
                string output(8, '0');
                for (int i = 7; i >= 0; i--) {
                        output[i] = (num & 1) ? '1' : '0';
                        num >>= 1;
                }
                return output;
        }

        string msgSize(int num) { // Decimal to binary (64-bit)
                if (num == 0) return "0000000000000000000000000000000000000000000000000000000000000000";
                string temp = "";
                while (num > 0) {
                        int remainder = num % 2;
                        temp += ('1' + remainder - 1);
                        num = num / 2;;
                }

                while (temp.size() < 64) temp += '0';

                string output = "                                                                ";
                for (int i = 0; i < 64; i++) output[63-i] = temp[i];
                return output;
        }

        string hexToBin(string l) {     // 32-bit binary
                if (l.size() == 0) return "00000000000000000000000000000000";
                if (l.size() > 2) if (l[0] == '0' and l[0] == 'x') l = l.substr(2,l.size()-2);
                
                string output;
                for (int i = 0; i < l.size() ; i++) {
                        int temp;
                        if (l[i] >= '0' and l[i] <= '9') {
                                temp = l[i] - '0';
                        } else if (l[i] >= 'a' and l[i] <= 'f') {
                                temp = l[i] - 'a' + 10;
                        }
                        
                        bool digit[4] = {false,false,false,false};
                        if (temp >= 8) {
                                temp -= 8;
                                digit[0] = true;
                        }
                        if (temp >= 4) {
                                temp -= 4;
                                digit[1] = true;
                        }
                        if (temp >= 2) {
                                temp -= 2;
                                digit[2] = true;
                        }
                        if (temp >= 1) {
                                temp -= 1;
                                digit[3] = true;
                        }
                        
                        for (int i = 0; i < 4; i++) {
                                if (digit[i]) output += '1';
                                else output += '0';
                        }
                }
                
                return output;
        }

        string textToBin(string l) {
                string n = "";
                for (int i = 0; i < l.size(); i++) {
                        n += (toBin(l[i]));
                }

                return n;
        }

        string preProccess(string l) {
                l += '1';
                // Calculate zeros needed: paddedLength - msgLength - 65
                int zeros_needed = paddedLength - msgLength - 65;
                l += string(zeros_needed, '0');
                l += msgSize(msgLength);
                return l;
        }

        char chunkToChar(string l) {
                int n = 0;
                
                while (l.size() < 4) {
                        l = '0' + l;
                }
                
                if (l[0] == '1') n += 8;
                if (l[1] == '1') n += 4;
                if (l[2] == '1') n += 2;
                if (l[3] == '1') n += 1;
                
                if (n < 10) {
                        return '0' + n;
                } else {
                        return 'a' + (n - 10);
                }
            }
    
        string binToHex(string l) {
                string head = "-";
                string chunk[(l.size() / 4)];
                int count = 0;
                if (l.size() % 4 != 0) {
                        head = l.substr(0,l.size() % 4);
                }
                    
                l = l.substr(l.size() % 4, l.size() - (l.size() % 4));
                    
                for (int i = 0; i < l.size(); i++) {
                        chunk[count] += l[i];
                        if ((i + 1) % 4 == 0) {
                                count++;
                        }
                }
                    
                string output = "";
                if (head != "-") output += chunkToChar(head);
                for (int i = 0; i < (l.size() / 4); i++) {
                        output += chunkToChar(chunk[i]);
                }
                    
                return output;
        }

        string computation(string l) {
                resetHashValue();
                string m[16];
                for (int i = 0; i < 16; i++) {
                        m[i] = l.substr(i * 32,32);
                }

                string w[64];
                for (int i = 0; i < 64; i++) {
                        w[i] = "00000000000000000000000000000000";
                }
                for (int i = 0; i < 16; i++) {
                        w[i] = m[i];
                }

                for (int i = 16; i < 64; i++) {
                        w[i] = addtion(addtion(addtion(w[i-16], sigma0(i,w)), w[i-7]), sigma1(i,w));
                }

                string value[8];
                for (int i = 0; i < 8; i++) value[i] = hexToBin(h[i]);

                for (int i = 0; i < 64; i++) {
                        string S1, S0, ch, maj, temp1, temp2;
                        S1 = xOR(rightRotate(value[4],6), xOR(rightRotate(value[4],11),rightRotate(value[4],25)));
                        S0 = xOR(rightRotate(value[0],2), xOR(rightRotate(value[0],13),rightRotate(value[0],22)));
                        ch = xOR(AND(value[4],value[5]),AND(NOT(value[4]),value[6]));
                        maj = xOR(AND(value[0],value[1]), xOR(AND(value[0],value[2]), AND(value[1],value[2])));
                        temp1 = addtion(value[7],addtion(S1,addtion(ch,addtion(hexToBin(k[i]),w[i]))));
                        temp2 = addtion(S0, maj);

                        value[7] = value[6];
                        value[6] = value[5];
                        value[5] = value[4];
                        value[4] = addtion(value[3],temp1);
                        value[3] = value[2];
                        value[2] = value[1];
                        value[1] = value[0];
                        value[0] = addtion(temp1,temp2);

                }

                for (int i = 0; i < 8; i++) {
                        h[i] = addtion(hexToBin(h[i]),value[i]);
                }

                string output;
                for (int i = 0; i < 8; i++) {
                        output += h[i];
                }

                return binToHex(output);
        }

        public:

        void test(string l) {
                getMsgLen(l);
                getPadLen(l);   
                string temp = preProccess(textToBin((l)));
                cout << endl << computation(temp) << endl;
        }
};

int main() {
        SHA256 test;
        string l = "";
        cin >> l;
        test.test(l);
}
