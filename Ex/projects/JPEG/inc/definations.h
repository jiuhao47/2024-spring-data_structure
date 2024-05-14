#define FILE_PLACE "../test/Blue hills.jpg"
#define READ_LEN 600

#define JPEG_FORMAT_LEN 4
#define JPEG_FORMAT_START 6

// Start of Image
#define MARKER_SOI 0xd8
// JFIF application segment
#define MARKER_APP0 0xe0
// #define MARKER_APPn
// Other APP segments

// Quantization Table
#define MARKER_DQT 0xdb
// Start of Frame
#define MARKER_SOF0 0xc0
// Huffman Table
#define MARKER_DHT 0xc4
// Start of Scan
#define MARKER_SOS 0xda
// End of Image
#define MARKER_EOI 0xd9