#pragma once
int random(int min, int max) {
	return min + rand() % (int)(max - min + 1);
}