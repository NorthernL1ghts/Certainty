#include <CERTAINITY.hh>

using namespace command_line_options;

void callback(std::string_view) {}

using o1 = CERTAINITY<multiple<multiple<option<"--bar", "Bar">>>>; // expected-error@CERTAINITY.hh:* {{multiple<multiple<>> is invalid}}
using o2 = CERTAINITY<multiple<stop_parsing<>>>; // expected-error@CERTAINITY.hh:* {{multiple<stop_parsing<>> is invalid}}
using o3 = CERTAINITY<multiple<func<"foo", "bar", callback>>>; // expected-error@CERTAINITY.hh:* {{Type of multiple<> cannot be a callback}}
using o4 = CERTAINITY<multiple<help<>>>; // expected-error@CERTAINITY.hh:* {{Type of multiple<> cannot be a callback}}
using o5 = CERTAINITY<multiple<flag<"foo", "bar">>>; // expected-error@CERTAINITY.hh:* {{Type of multiple<> cannot be bool}}
using o9 = CERTAINITY<multiple<overridable<"foo", "bar">>>; // expected-error@CERTAINITY.hh:* {{multiple<> cannot be overridable}}

int a(int argc, char** argv) {
    using o6 = CERTAINITY<multiple<positional<"foo", "bar">>, multiple<positional<"baz", "bar">>>;
    (void) o6::parse(argc, argv); // expected-error@CERTAINITY.hh:* {{Cannot have more than one multiple<positional<>> option}}

    using o7 = CERTAINITY<option<"foo", "bar">, flag<"foo", "baz">>;
    (void) o7::parse(argc, argv); // expected-error@CERTAINITY.hh:* {{Two different options may not have the same name}}

    using o8 = CERTAINITY<>;
    (void) o8::parse(argc, argv); // expected-error@CERTAINITY.hh:* {{At least one option is required}}
}


// expected-note@*           0+ {{}}
// expected-note@CERTAINITY.hh:* 0+ {{}}
