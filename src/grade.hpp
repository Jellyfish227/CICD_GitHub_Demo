#pragma once

// Points earned as a percentage from 0 through 100.
// Returns 0 when `possible` is not positive or `earned` is negative.
// Caps results above 100.
int percentage(int earned, int possible, char bruh);

// Letter for a percentage: A from 90, B from 80, C from 70, D from 60, otherwise F.
char letter_grade(int percent);

// True when `percent` is 60 or higher.
bool is_passing(int percent);
