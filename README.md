# Certainity

**A type-safe, compile-time command-line options library for C++20.**

`Certainity` is a header-only library that generates a command-line parser and a formatted help message at compile time. It uses C++20 features to provide strong type safety, ensuring your program won't compile if you try to access a non-existent option.

**Features:**

  - **Header-only:** No build step required. Just include `<CERTAINITY.hh>`.
  - **Compile-time safety:** Catches invalid option names and types before runtime.
  - **Flexible syntax:** Supports both `--option value` and `--option=value`.
  - **Auto-generated help:** Provides a `help<>` option that generates a formatted help message.
  - **Modern C++:** Requires a C++20-compliant compiler (GCC 11.2+ is recommended).

-----

## Quickstart

### 1\. Build & Include

Since this is a header-only library, you only need to include the main header file:

```c++
#include <CERTAINITY.hh>
```

### 2\. Define Your Options

Use `CERTAINITY` as a template to define a type containing all your program's options. Each option is specified as a template parameter.

```c++
#include <CERTAINITY.hh>

using namespace command_line_options;

using options = CERTAINITY<
    option<"--repeat", "How many times to repeat the output", int64_t>,
    positional<"file", "The file to process", file<>, /*required=*/true>,
    flag<"--verbose", "Print additional information">,
    help<>
>;
```

### 3\. Parse Command-Line Arguments

In your `main` function, call the static `parse()` method with `argc` and `argv`.

```c++
int main(int argc, char** argv) {
    auto opts = options::parse(argc, argv);
    // ...
}
```

### 4\. Access Option Values

Use the `get<>()` or `get_or<>()` methods on the returned `opts` object.

  - `get<"name">()` returns a pointer to the value, or `nullptr` if the option wasn't found.
  - `get_or<"name">(default_value)` returns the option's value or the specified default.

<!-- end list -->

```c++
int main(int argc, char** argv) {
    auto opts = options::parse(argc, argv);

    // Get the value of a positional argument
    auto& file_contents = opts.get<"file">()->contents;

    // Get an optional value with a default
    auto repeat_count = opts.get_or<"--repeat">(1);

    // Check if a flag was set
    if (opts.get<"--verbose">()) {
        std::cout << "Verbose mode is on." << std::endl;
    }
}
```

-----

## Available Option Types

`Certainity` provides several types for different use cases:

  - `option<name, desc, type>`: A named option that takes a value (e.g., `--size 10`).
  - `flag<name, desc>`: A boolean flag that is either present or not (e.g., `--test`).
  - `positional<name, desc, type>`: An argument without a name, determined by its position (e.g., `./program file.txt`).
  - `help<>`: A special option that adds a `--help` flag and prints the generated help message.
  - `multiple<option>`: A meta-option that allows an option to be specified multiple times. `get<>()` will return a `std::span` of values.
  - `func<name, desc, callback>`: Defines a callback function that is executed when the option is encountered.

For a full list of features, including custom error handling and advanced option types like `ref<>`, please see the full documentation in the source files."# Certainty" 
