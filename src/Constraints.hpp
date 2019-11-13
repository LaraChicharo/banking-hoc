#pragma once

// Max number of pepople involved in the banking system
const int MAXPEOPLE = 2100;
// Virtual zero
const double VIRTUAL_ZERO = 1e-7;
/// Rate in with temperature is going to decrease
const double TEMPERATURE_DECAY = .99;
/// Percentage of
const double P = .97;
/// Initial temperature
const double INITIAL_TEMPERATURE = 1100;
/// Size of the batch
const int L = 5000;
/// Stop a batch after this many iterations it batch is still running
const int STOP = L * 3000;
