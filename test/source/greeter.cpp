#include <doctest/doctest.h>
#include <greeter/greeter.h>
#include <{#PROJECT_TITLE_LOWER#}/version.h>

#include <string>

TEST_CASE("{#PROJECT_TITLE#}") {
  using namespace greeter;

  Greeter {#PROJECT_TITLE#}("Tests");

  CHECK({#PROJECT_TITLE#}.greet(LanguageCode::EN) == "Hello, Tests!");
  CHECK({#PROJECT_TITLE#}.greet(LanguageCode::DE) == "Hallo Tests!");
  CHECK({#PROJECT_TITLE#}.greet(LanguageCode::ES) == "¡Hola Tests!");
  CHECK({#PROJECT_TITLE#}.greet(LanguageCode::FR) == "Bonjour Tests!");
}

TEST_CASE("{#PROJECT_TITLE#} version") {
  static_assert(std::string_view({#PROJECT_TITLE_UPPER#}_VERSION) == std::string_view("0.1"));
  CHECK(std::string({#PROJECT_TITLE_UPPER#}_VERSION) == std::string("0.1"));
}
