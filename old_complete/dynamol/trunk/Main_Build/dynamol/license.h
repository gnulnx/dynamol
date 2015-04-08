//  //
// #     #####  ###                -= License library =-                 //
// #       #   #   # License.h - License key coder                       //
// #       #   #                                                         //
// #       #   #     Encodes and decodes 5x5 digit license keys          //
// #       #   #   #                                                     //
// ##### #####  ###  R1             (C)2003 Markus Ewald -> License.txt  //
//  //
#ifndef LIC_LICENSE_H
#define LIC_LICENSE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

namespace LicenseKey {

#ifndef LIC_NO_ENCODER
  /// Encode a license key from 4 longs
  inline std::string encode(const unsigned long pnData[4]);
  /// Encode a license key with bit mixing
  inline std::string encode(
    const unsigned long pnData[4], const unsigned char pcBitPositions[128]
  );
#endif
    
#ifndef LIC_NO_DECODER
  /// Decode a license key into 4 longs
  inline void decode(const std::string &sCoded, unsigned long pnData[4]);
  /// Decode a license key with bit mixing
  inline void decode(
    const std::string &sCoded, unsigned long pnData[4],
    const unsigned char pcBitPositions[128]
  );
#endif

};

#ifndef LIC_NO_ENCODER
// ####################################################################### //
// # LicenseKey::encode()                                                # //
// ####################################################################### //
/** Encodes the 4 longs into a license key

    @param  pnData  4 long integer values to encode
    @return The encoded license key
*/
inline std::string LicenseKey::encode(const unsigned long pnData[4]) {
  static const unsigned char pcBitPositions[128] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
     10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
     20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
     40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
     50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
     70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
     80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
     90,  91,  92,  93,  94,  95,  96,  97,  98,  99,
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127
  };

  return encode(pnData, pcBitPositions);
}

// ####################################################################### //
// # LicenseKey::encode()                                                # //
// ####################################################################### //
/** Encodes the 4 longs into a license key and performs bit-mixing on
    the individual bits to make the data less traceable.

    @param  pnData          4 long integer values to encode
    @param  pcBitPositions  Bit positions, has to contain each
                            number from 0 to 127 exactly once
    @return The encoded license number
*/
inline std::string LicenseKey::encode(
  const unsigned long pnData[4], const unsigned char pcBitPositions[128]
) {
  typedef std::vector<bool> BoolVector;

  static const char pcEncodeTable[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
  static const unsigned long pn2Powers[32][2] = {
    { 0,         1 }, { 0,         2 }, { 0,          4 }, { 0,          8 },
    { 0,        16 }, { 0,        32 }, { 0,         64 }, { 0,        128 },
    { 0,       256 }, { 0,       512 }, { 0,       1024 }, { 0,       2048 },
    { 0,      4096 }, { 0,      8192 }, { 0,      16384 }, { 0,      32768 },
    { 0,     65536 }, { 0,    131072 }, { 0,     262144 }, { 0,     524288 },
    { 0,   1048576 }, { 0,   2097152 }, { 0,    4194304 }, { 0,    8388608 },
    { 0,  16777216 }, { 0,  33554432 }, { 0,   67108864 }, { 0,  134217728 }, 
    { 0, 268435456 }, { 0, 536870912 }, { 0, 1073741824 }, { 0, 2147483648 }
  };

  BoolVector Data(128);

  // Build a bit array from the input data
  for(unsigned int j = 0; j < 4; j++)
    for(unsigned int i = 0; i < 32; i++)
      Data[pcBitPositions[j * 32 + i]] = (pnData[j] & pn2Powers[i][1]) != 0;

  // Build 4 sequences of 6 characters from the first 124 bits
  std::string sResult;    
  for(unsigned int i = 0; i < 4; i++) {
    unsigned long nSequence = 0;
    for(unsigned int j = 0; j < 31; j++)
      nSequence |= pn2Powers[j][Data[i * 31 + j] ^ ((i * 31 + j) & 1)];

    sResult += pcEncodeTable[nSequence % 36];
    cout << pcEncodeTable[nSequence % 36] << endl;
    nSequence /= 36;
    sResult += pcEncodeTable[nSequence % 36];
    nSequence /= 36;
    sResult += pcEncodeTable[nSequence % 36];
    nSequence /= 36;
    sResult += pcEncodeTable[nSequence % 36];
    nSequence /= 36;
    sResult += pcEncodeTable[nSequence % 36];
    nSequence /= 36;
    sResult += pcEncodeTable[nSequence % 36];
    
    cout <<"sResult: "<< sResult << endl;
  }

  // Use the remaining 4 bits to build the final character
  unsigned long nSequence = pn2Powers[4][ Data[124]] |
                            pn2Powers[3][!Data[125]] |
                            pn2Powers[2][ Data[126]] |
                            pn2Powers[1][!Data[127]] |
                            pn2Powers[0][1];

  return sResult.substr( 0, 5) + "-" + 
         sResult.substr( 5, 5) + "-" +
         sResult.substr(10, 5) + "-" +
         sResult.substr(15, 5) + "-" +
         sResult.substr(20, 5) + pcEncodeTable[nSequence];
};
#endif // LIC_NO_ENCODER

#ifndef LIC_NO_DECODER
// ####################################################################### //
// # License::decode()                                                   # //
// ####################################################################### //
/** Decodes a license key into 4 longs

    @param  sCoded  Coded license key
    @param  pnData  4 long integer values to receive the decoded data
*/
inline void LicenseKey::decode(const std::string &sCoded, unsigned long pnData[4]) {
  //cout <<"HERE 1: " << endl;
  static const unsigned char pcBitPositions[128] = {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
     10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
     20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
     40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
     50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
     70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
     80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
     90,  91,  92,  93,  94,  95,  96,  97,  98,  99,
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127
  };
  //cout <<"HERE 2"<<endl;
  decode(sCoded, pnData, pcBitPositions);
}

// ####################################################################### //
// # LicenseKey::decode()                                                # //
// ####################################################################### //
/** Decodes a license key into 4 longs and resolves bit-mixing performed
    on the individual bits

    @param  sCoded  Coded license key
    @param  pnData  4 long integer values to receive the decoded data
    @param  pcBitPositions  Bit positions, has to contain each
                            number from 0 to 127 exactly once
*/
inline void LicenseKey::decode(
  const std::string &sCoded, unsigned long pnData[4],
  const unsigned char pcBitPositions[128]
) {
  //cout <<"HERE 1"<<endl;
  typedef std::vector<bool> BoolVector;

  static const unsigned long pn2Powers[32][2] = {
    { 0,         1 }, { 0,         2 }, { 0,          4 }, { 0,          8 },
    { 0,        16 }, { 0,        32 }, { 0,         64 }, { 0,        128 },
    { 0,       256 }, { 0,       512 }, { 0,       1024 }, { 0,       2048 },
    { 0,      4096 }, { 0,      8192 }, { 0,      16384 }, { 0,      32768 },
    { 0,     65536 }, { 0,    131072 }, { 0,     262144 }, { 0,     524288 },
    { 0,   1048576 }, { 0,   2097152 }, { 0,    4194304 }, { 0,    8388608 },
    { 0,  16777216 }, { 0,  33554432 }, { 0,   67108864 }, { 0,  134217728 }, 
    { 0, 268435456 }, { 0, 536870912 }, { 0, 1073741824 }, { 0, 2147483648 }
  };

  static const unsigned char pcDecodeTable[256] = {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,  0,  0,  0,  0,
     0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,  0,  0,  0,  0,  0,
     0, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
  };

  BoolVector Data(128);

  // Remove all minus signs from the string
  std::string sTemp(sCoded);
  while(std::string::size_type Pos = sTemp.find_first_of(" -")) {
    if(Pos == std::string::npos)
      break;

    sTemp.erase(Pos, 1);
  }

  // Convert the first 4 sequences of 6 chars into 124 bits
  for(int j = 0; j < 4; j++) {
    unsigned long nSequence = pcDecodeTable[sTemp[j * 6 + 5]] * 60466176 +
                              pcDecodeTable[sTemp[j * 6 + 4]] *  1679616 +
                              pcDecodeTable[sTemp[j * 6 + 3]] *    46656 +
                              pcDecodeTable[sTemp[j * 6 + 2]] *     1296 +
                              pcDecodeTable[sTemp[j * 6 + 1]] *       36 +
                              pcDecodeTable[sTemp[j * 6 + 0]];

    for(unsigned int i = 0; i < 31; i++)
      Data[j * 31 + i] = ((nSequence & pn2Powers[i][1]) != 0) ^ ((j * 31 + i) & 1);
  }

  // Append the remaining character's 4 bits
  unsigned long nSequence = pcDecodeTable[sTemp[24]];
  Data[124] = (nSequence & pn2Powers[4][1]) != 0;
  Data[125] = (nSequence & pn2Powers[3][1]) == 0;
  Data[126] = (nSequence & pn2Powers[2][1]) != 0;
  Data[127] = (nSequence & pn2Powers[1][1]) == 0;

  // Convert the bit array into the desired output data
  for(int i = 0; i < 4; i++) {
    pnData[i] = 0;
    for(int j = 0; j < 32; j++)
      pnData[i] |= pn2Powers[j][Data[pcBitPositions[i * 32 + j]]];
  }

  return;
}
#endif // LIC_NO_DECODER

#endif // LIC_LI



































