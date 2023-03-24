# Aranet Home Test

## Task - bytes to json

Create a C/C++ commandline program that fulfills the following requirements:

- Takes input in the form of either
  - 8 byte hex numbers
  - 8 bytes encoded with base64
- Packs the input bytes into the provided `content` struct
- Packs the values of the struct members into a JSON object, using the provided struct member names as keys
- Outputs the JSON so that it is both human-readable (indentation) and machinereadable (correct JSON syntax)

### Additional notes:

- Use the following test cases to validate your solution:
  - `E0ABAkmCAwQ=`
    - Output: **co2: 772; error: true; segment: 4**
  - `0x8730000837000258` => **co2: 600**
    - Output: **co2: 600**
- Code must compile using a reasonably **recent GCC** version on a **recent Ubuntu** distribution
- Provide either a `Makefile` or the bare terminal command to compile the code
- External libraries can be used, but must be included in the applicant's source code archive
- Provide the source code as a `.tar.gz` or `.zip` archive

```c++
struct content {
    uint16_t co2;
    uint8_t errCode : 6;
    uint8_t errType : 1;
    uint8_t error : 1;
    uint8_t reserved;
    uint32_t id : 20;
    uint32_t segment : 4;
    uint8_t reserved2;
};
```

# Compiling Code

Make sure to compile the code on recent Ubuntu distribution with recent GCC.

To compile the code, type `make` on terminal.

If you don't want to use Makefile, you can run `g++ -std=c++17 -I../lib -o aranet src/main.cpp` command to compile the code.

# Examples

## Encoded Base64 Value

Run `./aranet E0ABAkmCAwQ=` command.

Output will be:

```json
{
  "co2": 772,
  "errCode": 2,
  "errType": 0,
  "error": true,
  "id": 258,
  "reserved": 73,
  "reserved2": 19,
  "segment": 4
}
```

---

## 8 Byte Hex Value

Run `./aranet 0x8730000837000258` command.

Output will be:

```json
{
  "co2": 600,
  "errCode": 0,
  "errType": 0,
  "error": false,
  "id": 8,
  "reserved": 55,
  "reserved2": 135,
  "segment": 3
}
```

# Code Explanation

Program firstly checking given value if hex or base64.

If the value is hex, it packs the hex code into content struct.

If value is base64, it decode the base64 and convert to hex. Then it packs the converted hex code into content struct.

To decode the given base64 value, I used [cppcodec](https://github.com/tplgy/cppcodec) library.

Finally, I used [nlohmann json](https://github.com/nlohmann/json) library for parse the content into json.

---
[Furkan KURT](https://furkankurt.com.tr/)