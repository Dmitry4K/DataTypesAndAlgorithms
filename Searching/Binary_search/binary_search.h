#pragma once
template<typename T>
int binary_search(T* arr, T Key) {
	bool found = false;
	int left = 0;
	int right = sizeof(arr) - 1;
	int middle;

	while ((left <= right) && (found != true)) {
		middle = (left + right) / 2;//находим средний индекс в отрезке
		if (arr[middle] == Key) found = true; //
		else if (arr[middle] > Key) right = middle - 1;
		else left = middle + 1;
	}

	if (found) return middle;
	else return -1;
}
