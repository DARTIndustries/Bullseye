#pragma once

#include <commands/AbstractCommand.h>
#include <commands/LedCommand.h>
#include <commands/ServoCommand.h>
#include <stdint.h>
#include <cstdint>

union CommandUnion {
  uin32_t type;
  LedCommand led;
  ServoCommand servo;
};