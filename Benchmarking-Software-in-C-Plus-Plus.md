# 1 Overview

This document outlines how to properly benchmark software using C++11. Prior methods of benchmark before C++11 are not accurate. The document details how the prior techniques were not accurate and should be replaced with the techniques below.

## High Resolution Timer

The standard timer built into C is only a second timer. In order to get a good reading, you will need to use a finer timer resolution. The C++11 chrono library allows for a millisecond and finer grain timing though there is a lot of technical intricacies with x86_64 CPUs going on in the background. x86_64 doesn't have a standardized timer beside the second timer so how you get the time is hardware dependent. On ARM CPUs the timer is usually very easy to manipulate is usually a real microsecond timer. On x86, however, you may only get a timer interval that is the same as the operating system update, which is probably just fine for your needs.

```C++
#include <chrono>
using namespace std::chrono;

int main () {
  auto start = high_resolution_clock::now (),
          stop  = high_resolution_clock::now ();
  auto delta = duration_cast<milliseconds>
                  (stop - start).count ();
  static double period = (double)std::chrono::high_resolution_clock::period::num /
    std::chrono::high_resolution_clock::period::den;
  std::cout << "\nperiod:" << period;
}
```

### Default Resolution of Clock

 Last time I checked the default period of the `std::chrono::high_resolution_clock`, it was a maximum of a nanosecond clock.

## Random Numbers

The standard random number generator in C is complete poo. You can actually see the bit pattern move across the bit fields with the clock cycle ticker. If you are testing with random numbers you will not go down all your paths without a true random number generator. Thankfully the C++ folks make the random library.

```C++
#include <random>

std::random_device rd;
std::mt19937_64 eng (rd ());
std::uniform_int_distribution<uint32_t> distr;

uint32_t value = distr (eng);
```

## Nil Measurement

There is a big difference between Execution Time and Processor Time. Processor time is the exact number of CPU cycles that software takes while CPU time includes the operating system overhead. Execution Time, on the other hand, includes the rest of the code running the operating system and running applications. Because of this, you tend to bet a Nil Measurement with a function that has the same setup as your algorithm. It is very important that you do not have any gimmicks that make your software look rosier when it's not.

Below is an example of an integer-to-string algorithm benchmark using the Nil Measurement and sprintf_s as a baseline. Please note that for the Nil Measurement a random number was generated and the error conditions checked.

```C++
char* PrintNil (uint32_t value, char* text, char* text_end) {
    if (!text) {
        return nullptr;
    }
    if (text > text_end) {
        return nullptr;
    }
    return text;
}
char* PrintSprintf (uint32_t value, char* text, char* text_end) {
    char buffer[24];
    if (!text) {
        return nullptr;
    }
    if (text > text_end) {
        return nullptr;
    }
    sprintf_s (buffer, 24, "%u", value);
    return text;
}
```

## Startup and Unit Testing

When your application starts, there is some extra processing that occurs in the background. This will affect your nil reading. You also need to verify that you're algorithms are working so the beginning of the benchmark should run the unit test for the software under benchmark. You cannot, however, get a good reading while in debug mode so make sure you are in Release Mode. For this reason, your unit test should be in a function that is callable from outside of your unit test script.

## Creating the Graph

The easiest way to get a graph is to export your benchmark as a Comma Separated Values (.csv) file, import it into Excel or LibreOffice, save it to a spreadsheet file, and create a graph in that .xlsx or similar file. It may also be just as easy to create a Matlab/Python/etc script rather than a .csv file.

### Redirection of cout

The best way to export the benchmark is by redirecting the C++ cout to write to a file.

### Example Code

Below is the benchmark for the integer-to-string algorithms from the Nil Measurement section. The last value in the list is an example of how you can show what percent faster or slower the benchmark is.

```C++
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

double nil_time,
       cpu_times[5];

static const char kBenchmarkHeader[] = "\nScript ItoS Benchmarks,,,,"
                                        "\n#Bits, Null, Mod10, "
                                        "Mod100, Script, % Faster\n";

ofstream file ("itos_benchmarks.csv");

if (!file.is_open ()) {
    cout << "Unable to open file";
    return;
}

cout << kBenchmarkHeader;
file << kBenchmarkHeader;
for (int num_bits = 1; num_bits <= 32; ++num_bits) {
    bits_mask = bits_mask << 1;
    value_mask = ~bits_mask;
    file << num_bits << ",";
    cout << '\n' << num_bits << ".) ";

    start = high_resolution_clock::now ();
    for (count = kNumTests; count > 0; --count) {
        value = distr (eng) & value_mask;
        result = PrintNil (value, text, text + kSize);
    }
    stop = high_resolution_clock::now ();
    delta = duration_cast<milliseconds> (stop - start).count ();
    nil_time = (double)delta;
    file << delta << ',';
    cout << delta << ',';

    start = high_resolution_clock::now ();
    for (count = kNumTests; count > 0; --count) {
        value = distr (eng) & value_mask;
        result = PrintSprintf (value, text, text + kSize);
    }
    stop = high_resolution_clock::now ();
    delta = duration_cast<milliseconds> (stop - start).count ();
    cpu_times[0] = (double)delta;
    file << delta << ',';
    cout << delta << ',';

    start = high_resolution_clock::now ();
    for (count = kNumTests; count > 0; --count) {
        value = distr (eng) & value_mask;
        result = PrintMod10 (value, text, text + kSize);
    }
    stop = high_resolution_clock::now ();
    delta = duration_cast<milliseconds> (stop - start).count ();
    cpu_times[1] = (double)delta;
    file << delta << ',';
    cout << delta << ',';

    start = high_resolution_clock::now ();
    for (count = kNumTests; count > 0; --count) {
        value = distr (eng) & value_mask;
        result = PrintMod100 (value, text, text + kSize);
    }
    stop = high_resolution_clock::now ();
    delta = duration_cast<milliseconds> (stop - start).count ();
    cpu_times[2] = (double)delta;
    file << delta << ',';
    cout << delta << ',';

    start = high_resolution_clock::now ();
    for (count = kNumTests; count > 0; --count) {
        value = distr (eng) & value_mask;
        result = _::Print (value, text, text + kSize);
    }
    stop = high_resolution_clock::now ();
    delta = duration_cast<milliseconds> (stop - start).count ();
    cpu_times[3] = (double)delta;
    file << delta << ',';
    cout << delta << ',';
    double percent_faster = ((cpu_times[2] - nil_time) / (cpu_times[3] - nil_time))
                          - 1.0;
    file << percent_faster << '\n';
    cout << percent_faster;
}
file.close ();
```

### OpenOffice Calc Screenshot

![Mod 100 LUT vs Puff ItoS Benchmarks Per Bit Count](https://github.com/kabuki-starship/kabuki-toolkit/wiki/script_itos_benchmark.jpg)

![Mod 100 LUT vs Puff ItoS Benchmarks Per Digit Count](https://github.com/kabuki-starship/kabuki-toolkit/wiki/script_itos_benchmark_per_digit_count.jpg)
