#include "my_jval_util.h"

void quickSort3WayJval(Jval *a, int l, int r, int (*compare)(Jval*, Jval*)) {
	if(r <= l)
		return;
	int i = l - 1, j = r;
	int p = l - 1, q = r;
	int k;

	while(1) {
		i++;
		while(compare(&a[i], &a[r]) < 0) { // Swap me
			i++;
		}
		j--;
		while(compare(&a[r], &a[j]) < 0) {
			if(j == l) {
				break;
			}
			j--;
		}

		if(i >= j) break; // Out of order

		exchangeJval(a, i, j);
		if(compare(&a[i], &a[r]) == 0) {
			exchangeJval(a, ++p, i);
		}
		if(compare(&a[j], &a[r]) == 0) {
			exchangeJval(a, --q, j);
		}
	}

	exchangeJval(a, i, r);
	j = i - 1;
	i = i + 1;
	
	for(k = l; k <= p; k++)
		exchangeJval(a, k, j--);
	for(k = r - 1; k >= q; k--)
		exchangeJval(a, k, i++);
	quickSort3WayJval(a, l, j, compare);
	quickSort3WayJval(a, i, r, compare);
}

int seqSearchJval(Jval *a, int amount, Jval item, int (*compare)(Jval*, Jval*)) {
	int i = 0, res;		

	while(i < amount) {
		res = compare(&item, &a[i]);
		if(res == 0)
			return i;
		i++;
	}

	if(i >= amount)
		return -1;
}

int binarySearchJval(Jval *a, Jval item, int low, int high, int (*compare)(Jval*, Jval*)) {
	int mid = midPoint(low, high);
	int res;

	if(low > high) {
		return -1;
	}

	res = compare(&a[mid], &item);
	if(res > 0) {
		return binarySearchJval(a, item, low, mid - 1, compare);
	}

	if(res < 0) {
		return binarySearchJval(a, item, mid + 1, high, compare);
	}

	return mid;
}

int midPoint(int low, int high) {
	return low + (high - low) / 2;
}

void exchangeJval(Jval *a, int i, int j) {
	Jval temp;

	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}