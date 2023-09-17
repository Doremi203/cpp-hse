#pragma once

#include <cstdio>

const int LINES = 10;
const int COLUMNS = 10;

using TableType = int[LINES][COLUMNS];

void BuildDiagonalArray(TableType table);
