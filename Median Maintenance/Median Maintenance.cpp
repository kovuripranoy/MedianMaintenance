#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void swap(double *a, double *b)
{
	double t = *b;
	*b = *a;
	*a = t;
}

class maxHeap
{
	double capacity;
public:
	double *harr;
	int heapsize;
	maxHeap(double capacity);
	int parent(double i) { return ((int)i - 1) / 2; }
	int left(double i) { return 2 * (int)i + 1; }
	int right(double i) { return 2 * (int)i + 2; }
	double extractMax();
	double getMax() { return harr[0]; }
	void insertKey(double k);
	double getSize() { return heapsize; }
};
maxHeap::maxHeap(double cap)
{
	harr = new double[cap];
	capacity = cap;
	heapsize = 0;
}
void maxHeap::insertKey(double k)
{
	if (heapsize == capacity)
	{
		cout << "Overflow";
		return;
	}
	heapsize += 1;
	int i = heapsize - 1;
	harr[i] = k;
	while (i != 0 && harr[parent(i)] < harr[i])
	{
		swap(&harr[parent(i)], &harr[i]);
		i = parent(i);
	}

}
double maxHeap::extractMax()
{
	swap(&harr[heapsize - 1], &harr[0]);
	if (heapsize == 1)
	{
		heapsize--;
		return harr[0];
	}
	heapsize -= 1;
	int i = 0;
	while ((right(i)<heapsize) || (left(i)<heapsize))
	{
		if ((harr[left(i)] < harr[right(i)]) && (harr[right(i)] > harr[i]) && (right(i)<heapsize))
		{
			swap(&harr[right(i)], &harr[i]);
			i = right(i);

		}
		else if ((harr[left(i)] > harr[right(i)]) && (harr[left(i)] > harr[i]) && (left(i)<heapsize))
		{
			swap(&harr[left(i)], &harr[i]);
			i = left(i);
		}
		else if (right(i) == heapsize && (harr[left(i)] > harr[i]))
		{
			swap(&harr[left(i)], &harr[i]);
			i = left(i);
		}
		else
		{
			break;
		}
	}
	//cout<<harr[heapsize]<<endl;
	//cout << "Array NOw";
	/*for (double i = 0; i < heapsize; i++)
	{
		
		cout << harr[i]<<",";
	}*/
	//cout << endl;
	return harr[heapsize];
}

class minHeap
{
	double capacity;
public:
	double *harr;
	int heapsize;
	minHeap(double capacity);
	int parent(double i) { return ((int)i - 1) / 2; }
	int left(double i) { return 2 * (int)i + 1; }
	int right(double i) { return 2 * (int)i + 2; }
	double extractMin();
	double getMin() { return harr[0]; }
	void insertKey(double k);
	double getSize() { return heapsize; }
};
minHeap::minHeap(double cap)
{
	harr = new double[cap];
	capacity = cap;
	heapsize = 0;
}
void minHeap::insertKey(double k)
{
	if (heapsize == capacity)
	{
		cout << "Overflow";
		return;
	}
	heapsize += 1;
	int i = heapsize - 1;
	harr[i] = k;
	while (i != 0 && harr[parent(i)] > harr[i])
	{
		swap(&harr[parent(i)], &harr[i]);
		i = parent(i);
	}

}
double minHeap::extractMin()
{
	swap(&harr[heapsize - 1], &harr[0]);
	if (heapsize == 1)
	{
		heapsize--;
		return harr[0];
	}
	heapsize -= 1;
	int i = 0;
	while ((right(i)<heapsize) || (left(i)<heapsize))
	{
		if ((harr[left(i)] > harr[right(i)]) && (harr[right(i)] < harr[i]) && (right(i)<heapsize))
		{
			swap(&harr[right(i)], &harr[i]);
			i = right(i);

		}
		else if ((harr[left(i)] < harr[right(i)]) && (harr[left(i)] < harr[i]) && (left(i)<heapsize))
		{
			swap(&harr[left(i)], &harr[i]);
			i = left(i);
		}
		else if ((harr[left(i)] < harr[i]) && (right(i) == heapsize))
		{
			swap(&harr[left(i)], &harr[i]);
			i = left(i);
		}
		else
		{
			break;
		}
	}
	//cout<<harr[heapsize]<<endl;
	return harr[heapsize];
}

int main()
{

	ifstream instream;
	instream.open("Median.txt");
	/*if (instream.is_open()) {
		cout << "Successfully openend file for reading 0.\n";
	}*/
	
	
	double * input = new double[10000];
	int count = 0;
	long sum =0;
	while (!instream.eof())
	{
		instream >> input[count];
		count += 1;
	}
	/*for (double i=0;i<count;i++)
	cout <<"\nInput element "<<count<<"\t" <<input[i];
	*///cout<<endl<<endl;
	maxHeap maxHeapObj(10000);
	minHeap minHeapObj(10000);
	double *median = new double[10000];
	int i = 0;
	while (i < count)
	{
		{
		    /* If the elements are zeros*/
			if (minHeapObj.heapsize == 0 && maxHeapObj.heapsize != 0)
			{
				minHeapObj.insertKey(input[i]);
				//cout << "\nminHeapSize\n";
				if (maxHeapObj.getMax() > minHeapObj.getMin())
					swap(maxHeapObj.harr, minHeapObj.harr);
				goto done;
			}
			if (maxHeapObj.heapsize == 0)
			{
				maxHeapObj.insertKey(input[i]);
				//cout << "maxHeapSize\n";
				
				goto done;
			}	
			
		}
		{
	        /*make sure the heaps differ by a factor of 1*/
			
			
			/*Insert the element*/
	
			if (input[i] > minHeapObj.getMin())
				minHeapObj.insertKey(input[i]);
			else
				maxHeapObj.insertKey(input[i]);
			
			if (minHeapObj.heapsize == maxHeapObj.heapsize + 2)
			{
				maxHeapObj.insertKey(minHeapObj.extractMin());
			}
			if (minHeapObj.heapsize + 2 == maxHeapObj.heapsize)
			{
				minHeapObj.insertKey(maxHeapObj.extractMax());
			}
		}
		done:
		{
			/*Assigning the median*/
			if ((minHeapObj.heapsize % 2) == 0 && (maxHeapObj.heapsize % 2) == 0)
				median[i] = maxHeapObj.getMax();
			else if (minHeapObj.heapsize > maxHeapObj.heapsize)
				median[i] = minHeapObj.getMin();
			else
				median[i] = maxHeapObj.getMax();
		}
		sum += median[i];
		cout << "Median["<<i<<"] :"<<median[i]<<endl;
		i++;
	}
	//maxHeap maxHeapObj(20);
	//maxHeapObj.insertKey(2);
	//maxHeapObj.insertKey(8);
	//maxHeapObj.insertKey(1);
	//maxHeapObj.insertKey(18);
	//maxHeapObj.insertKey(12);
	////double j = maxHeapObj.getMax();
	////for (double i = 0; i < 5; i++)
	////{
	////j = maxHeapObj.extractMax();
	////cout << j << endl;
	////}
	/////*for (double i = 0; i < 5; i++)
	////{
	////	j = maxHeapObj.harr[i];
	////	cout << j << endl;
	////}*/
	cout << "\nMedian percentile 10000  Ans = " << (sum % 10000);
	//cout << "\n\n\n\n\n\nDebugging\n";
	//double j;
	//cout << "MaxHeap  :  ";
	//for (double i = 0; i < maxHeapObj.heapsize; i++)
	//{
	//	j = maxHeapObj.harr[i];
	//	cout << j << "\t";
	//}
	//cout << "\nMinHeap  :  ";
	//for (double i = 0; i < minHeapObj.heapsize; i++)
	//{
	//	j = minHeapObj.harr[i];
	//	cout << j << "\t";
	//}
	return 0;
}