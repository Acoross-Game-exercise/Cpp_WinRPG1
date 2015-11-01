#pragma once

#define NO_COPY(x) x(const x&) = delete; x& operator=(const x&) = delete;

