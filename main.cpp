#include <iostream>
using namespace std;

class SHA256{
        private:
        int msgLength;  // In bit of binary
        int paddedLength;

        // HASH VALUES
        string h0 = "6a09e667";         //6a09e667
        string h1 = "bb67ae85";         //bb67ae85
        string h2 = "3c6ef372";         //3c6ef372
        string h3 = "a54ff53a";         //a54ff53a
        string h4 = "510e527f";         //510e527f
        string h5 = "9b05688c";         //9b05688c
        string h6 = "1f83d9ab";         //1f83d9ab
        string h7 = "5be0cd19";         //5be0cd19

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
                int c = l.size() / 512;
                int r = l.size() % 512;
                int temp = c * 512;
                if (r > 0) temp += 512;
                paddedLength = temp;
        }

        string hexToBin(string l) {        // hex to 32 bit-binary
                if (l.size() >= 3) if (l[0] == '0' and l[1] == 'x') l = l.substr(2,l.size() - 2);
                if (l.size() == 1 and l[0] == 0) return "00000000000000000000000000000000";

                string output = "";
                for (int i = 0; i < l.size(); i++) {
                        char temp = l[size
                }
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

        string toBin(int num) { // Decimal to binary (8-bit)
                if (num == 0) return "00000000";
                string temp = "";
                while (num > 0) {
                        int remainder = num % 2;
                        temp += ('1' + remainder - 1);
                        num = num / 2;;
                }

                while (temp.size() < 8) temp += '0';

                string output = "        ";
                for (int i = 0; i < 8; i++) output[7-i] = temp[i];
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

        string hexToBin(string l) {
                int power = 0;
                for (int i = 0; i < l.size() ; i++) {

                }
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
                for (int i = msgLength; i < paddedLength - 65; i++) {
                        l += '0';
                }

                l += msgSize(msgLength);

                return l;
        }

        string computation(string l) {
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

                for (int i = 0; i < 64 ; i++) {
                        cout << w[i] << " ";
                        if ((i + 1) % 4 == 0) cout << endl;
                }
                return "";
        }

        public:

        void test(string l) {
                getMsgLen(l);
                getPadLen(l);
                string temp = preProccess(textToBin((l)));
                cout << computation(temp);
        }
};

int main() {
        SHA256 test;
        test.test("hello");
}
