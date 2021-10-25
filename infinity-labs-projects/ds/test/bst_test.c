/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      Shahar
* Description   Binary search tree test module
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/


#include <stdio.h>
#include "bst.h"

#define S_MSG(func) "SUCCESS: " #func " works as expected!\n"
#define _N_ "\033[0m"
#define _R_ "\033[0;31m"
#define _G_ "\033[0;32m"
#define _Y_ "\033[0;33m"
#define _P_ "\033[0;35m"
#define _B_ "\033[0;36m"
#define _BB_ "\033[1;36m"

int IsBefore(const void *prior, const void *next, void *param)
{
	return (size_t)prior < (size_t)next;
	(void)param;
}
/*
int Action(void *data, void *param)
{
	size_t tmp = (size_t)param;

	tmp += (size_t)data;

	param = (void *)tmp;

	return (tmp > (99)) ? (int)tmp : 0;
}
*/
int Action(void *data, void *param)
{
	if ((size_t)data > *(size_t *)param)
	{
		*(size_t *)param = (size_t)data;
		return 0;
	}
	return (int)(size_t)data;
}

int IsEmpTest(bst_t *bst, int status)
{
	return (status ^ BSTIsEmpty(bst)) ?
		!!printf(_G_ S_MSG(BSTIsEmpty) _N_) :
		!(printf("%s", status ?
			_Y_"BSTIsEmpty "_R_"FAILED to recognize a "_Y_"full "_R_"tree"_N_ :
			_Y_"BSTIsEmpty "_R_"FAILED to recognize an "_Y_"empty "_R_"tree"_N_));
}

int SizeTest(bst_t *bst, size_t size)
{
	return (size == BSTSize(bst)) ?
		!!printf(_G_ S_MSG(BSTSize) _N_) :
		!printf(_Y_"BSTSize "_R_"FAILED to return "_Y_"%lu"_R_
				", instead got "_Y_"%lu\n"_N_, size, BSTSize(bst));
}

bst_iter_t InserTest(bst_t *bst, void *data)
{
	size_t size_b4 = BSTSize(bst);
	bst_iter_t iter = BSTInsert(bst, data);

	printf("%s", (IsEmpTest(bst, 1) && SizeTest(bst, size_b4 + 1)) ?
			_G_ S_MSG(BSTSize) S_MSG(BSTInsert) _N_ :
			_R_"FAILED to "_Y_"BSTInsert "_R_"Properly\n"_N_);

	return iter;
}

bst_iter_t RemoveTest(bst_t *bst, bst_iter_t iter)
{
	size_t size_b4 = BSTSize(bst);
	void *data = BSTGetData(iter);

	printf("%s", (data == BSTRemove(iter) && SizeTest(bst, size_b4 - 1)
			&& BSTIterIsEqual(BSTEnd(bst), BSTFind(bst, data))) ?
			_G_ S_MSG(BSTSize) S_MSG(IterIsEqual) S_MSG(BSTFind) S_MSG(BSTRemove) _N_ :
			_R_"FAILED to "_Y_"BSTRemove "_R_"Properly\n"_N_);

	return iter;
}

void OrderTest(bst_t *bst)
{
	size_t param = 0;
	int status = BSTForEach(BSTBegin(bst), BSTEnd(bst), &Action, &param);

	status ?
		printf(_R_"FAILED to correctly place "_Y_"%lu "
			_R_"before "_Y_"%d "_R_"in the tree\n"_N_, param, status) :
		printf(_G_ S_MSG(BSTBegin) S_MSG(BSTEnd) S_MSG(BSTForEach) S_MSG(tree order) _N_);
}

void XtremiTest(bst_t *bst)
{
	1 == (size_t)BSTGetData(BSTBegin(bst)) ?
		printf(_G_ S_MSG(BSTBegin) S_MSG(BSTGetData) _N_) :
		printf(_R_"FAILED to "_Y_"BSTGetData "_R_"from "_Y_"BSTBegin"_R_
			", instead got "_Y_"%lu\n", (size_t)BSTGetData(BSTBegin(bst)));
	0 == (size_t)BSTGetData(BSTEnd(bst)) ?
		printf(_G_ S_MSG(BSTEnd) S_MSG(BSTGetData) _N_) :
		printf(_R_"FAILED to "_Y_"BSTGetData 0 "_R_"from "_Y_"BSTEnd"_R_
			", instead got "_Y_"%p\n", BSTGetData(BSTEnd(bst)));
	2 == (size_t)BSTGetData(BSTNext(BSTBegin(bst))) ?
		printf(_G_ S_MSG(BSTNext) S_MSG(BSTGetData) _N_) :
		printf(_R_"FAILED to "_Y_"BSTGetData "_R_"from "_Y_"BSTBegin"_R_
			", instead got "_Y_"%lu\n", (size_t)BSTGetData(BSTNext(BSTBegin(bst))));
	256 == (size_t)BSTGetData(BSTPrev(BSTEnd(bst))) ?
		printf(_G_ S_MSG(BSTPrev) S_MSG(BSTGetData) _N_) :
		printf(_R_"FAILED to "_Y_"BSTGetData 0 "_R_"from "_Y_"BSTEnd"_R_
			", instead got "_Y_"%lu\n", (size_t)BSTGetData(BSTPrev(BSTEnd(bst))));
}

void FindTest(bst_t *bst, bst_iter_t iter)
{
	BSTIterIsEqual(iter, BSTFind(bst, BSTGetData(iter))) ?
		printf(_G_ S_MSG(BSTIterIsEqual) S_MSG(BSTFind) _N_) :
		printf(_R_"FAILED to "_Y_"BSTFind %lu "_R_"in the tree\n", (size_t)BSTGetData(iter));
}

void BSTest(void)
{
	size_t debug = 0;
	bst_t *bst = BSTCreate(&IsBefore, NULL);
	bst_iter_t i0 = NULL, i1 = NULL, i2 = NULL, i3 = NULL, i4 = NULL,
				i5 = NULL, i6 = NULL, i7 = NULL, i8 = NULL;

#ifndef NDEBUG
	debug = 1;
#endif /* NDEBUG */

	printf(_P_"\t\t%s\n\n"_B_"\tTesting "_BB_"BSTCreate\n"_N_,
			debug ? " Debug  mode" : "Release  mode");
	IsEmpTest(bst, 0);
	SizeTest(bst, 0);

	printf(_B_"\n\tTesting "_BB_"BSTInsert\n"_N_);
	i1 = InserTest(bst, (void *)8);
	i2 = InserTest(bst, (void *)128);
	i3 = InserTest(bst, (void *)4);
	i4 = InserTest(bst, (void *)1);
	i5 = InserTest(bst, (void *)32);
	i6 = InserTest(bst, (void *)16);
	i7 = InserTest(bst, (void *)2);
	i8 = InserTest(bst, (void *)64);
	i0 = InserTest(bst, (void *)256);

	printf(_B_"\n\tTesting tree order\n"_N_);
	XtremiTest(bst);
	OrderTest(bst);

	printf(_B_"\n\tTesting "_BB_"BSTFind\n"_N_);
	FindTest(bst, i5);
	FindTest(bst, i8);
	FindTest(bst, i2);
	FindTest(bst, i0);
	FindTest(bst, i6);
	BSTIterIsEqual(BSTEnd(bst), BSTFind(bst, (void *)0xFADEDACE)) ?
		printf(_G_ S_MSG(BSTIterIsEqual) S_MSG(BSTFind) _N_) :
		printf(_R_"FAILED to NOT"_Y_"BSTFind %u "_R_"in the tree\n", 0xFADEDACE);
	
	printf(_B_"\n\tTesting "_BB_"BSTRemove\n"_N_);
	RemoveTest(bst, i6);
	RemoveTest(bst, i2);
	RemoveTest(bst, i1);
	RemoveTest(bst, i4);
	RemoveTest(bst, i3);
	BSTDestroy(bst);
	(void)i0;
	(void)i1;
	(void)i2;
	(void)i3;
	(void)i4;
	(void)i5;
	(void)i6;
	(void)i7;
	(void)i8;
}

int main()
{
	printf(_BB_"\t\t~SJ BST TEST~\n"_N_);
	BSTest();
	printf(_B_"Please check "_P_"Valgrind "_B_
		"to ensure proper destruction!\n\t  ~Have a lovely day~\n"_N_);

	return 0;
}
