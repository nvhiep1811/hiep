#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LH -1  	 /* Cay con trai cao hon */
#define EH 0	 /* Hai cay con bang nhau */
#define RH 1 	 /* Cay con phai cao hon */

typedef struct tudien {
	char tuAnh[20];
	char nghia[20];
	char vidu[50];		
}TU;

struct AVLNode{
	char balFactor; //Chi so can bang
	TU Key;
	AVLNode* pLeft;
	AVLNode* pRight;
};
typedef AVLNode* AVLTree;

void themTu(AVLTree &T);
void NLR(AVLTree T);
void LNR(AVLTree T);
void LRN(AVLTree T);
int tinhH(AVLTree T);
AVLNode* timKiem(AVLTree T, char tuAnh[]);
int suaTu(AVLTree &T, char tuAnh[]);
void docFile(AVLTree &T1, char filename[], TU &x);
void ghiFile(AVLTree T, char filename[]);
//AVLTree
void rotateLL(AVLTree &T);
void rotateRR(AVLTree &T);
void rotateLR(AVLTree &T);
void rotateRL(AVLTree &T);
int balanceLeft(AVLTree &T);
int balanceRight(AVLTree &T);
int searchStandFor(AVLTree &p, AVLTree &q);
int insertNode(AVLTree &T, TU tu);
int delNode(AVLTree &T, char tuAnh[]);

int main(){
	AVLTree t;
	t = NULL;
	char tu[20], tuUp[20], tuDel[20];
	char c;
	do {
		fflush(stdin);
		themTu(t);
		printf("Tiep tuc them (y/n): ");scanf("%c", &c);
	} while(c == 'y');
	//Sua tu
	fflush(stdin);
	printf("Nhap tu can sua: ");gets(tuUp);
	if(suaTu(t, tuUp))
		printf("Sua thanh cong.\n");
	else if(suaTu(t, tuUp) == 0)
		printf("Tu khong ton tai.\n");
	else
		printf("Mang rong.\n");
	//Xoa tu
	printf("Nhap tu can xoa: ");gets(tuDel);
	if(delNode(t, tuDel) == 0)
		printf("Tu khong ton tai.\n");
	else
		printf("Xoa thanh cong.\n");
		
	//Xuat danh sach
	LNR(t);
	//Tim kiem tu
	fflush(stdin);
	printf("Nhap tu can tim kiem: ");gets(tu);
	AVLTree t1 = timKiem(t, tu);
	if(t1 == NULL)
		printf("Tu khong ton tai!!!\n");
	else {
		printf("Tim thay:\n%s: %s.\nExample: %s\n", t1->Key.tuAnh, t1->Key.nghia, t1->Key.vidu);
	}
	//Ghi danh sach vao file
	ghiFile(t, "T:/list.txt");
	AVLTree book;
	TU x;
	book = NULL;
	//Doc danh sach ra file
	docFile(book, "T:/list.txt", x);
	NLR(book);
}

void rotateLL(AVLTree &T) {
	AVLNode* T1 = T->pLeft;
	T->pLeft = T1->pRight;
	T1->pRight = T;
	switch(T1->balFactor) {
	case LH: T->balFactor = EH; 
	T1->balFactor = EH; 
	break;
	case EH: T->balFactor = LH;
	T1->balFactor = RH; 
	break;
	}
	T = T1;
}

void rotateRR(AVLTree &T) {
	AVLNode* T1 = T->pRight;
	T->pRight = T1->pLeft;
	T1->pLeft = T;
	switch(T1->balFactor) {
	case RH: T->balFactor = EH;
	T1->balFactor= EH; 
	break;
	case EH: T->balFactor = RH; 
	T1->balFactor= LH; 
	break;
	}
	T = T1;
}

void rotateLR(AVLTree &T) { 
	AVLNode* T1 = T->pLeft;
	AVLNode* T2 = T1->pRight;
	T->pLeft = T2->pRight;
	T2->pRight = T;
	T1->pRight = T2->pLeft;
	T2->pLeft = T1;
	switch(T2->balFactor) {
		case LH: 
			T->balFactor = RH; 
			T1->balFactor = EH; 
			break;
		case EH: 
			T->balFactor = EH; 
			T1->balFactor = EH; 
			break;
		case RH: 
			T->balFactor = EH; 
			T1->balFactor = LH; 
			break;
	}
	T2->balFactor = EH;
	T = T2;
}

void rotateRL(AVLTree &T) { 
	AVLNode* T1 = T->pRight;
	AVLNode* T2 = T1->pLeft;
	T->pRight = T2->pLeft;
	T2->pLeft = T;
	T1->pLeft = T2->pRight;
	T2->pRight = T1;
	switch(T2->balFactor) {
		case RH: 
			T->balFactor = LH; 
			T1->balFactor = EH; 
			break;
		case EH: 
			T->balFactor = EH; 
			T1->balFactor = EH; 
			break;
		case LH: 
			T->balFactor = EH; 
			T1->balFactor = RH; 
			break;
	}
	T2->balFactor = EH;
	T = T2;
}

int balanceLeft(AVLTree &T) {
	AVLNode* T1 = T->pLeft;
	switch(T1->balFactor) {
		case LH: 
			rotateLL(T); return 2;
		case EH: 
			rotateLL(T); return 1;
		case RH: 
			rotateLR(T); return 2;
	}
	return 0;
}

int balanceRight(AVLTree &T ) {
	AVLNode* T1 = T->pRight;
	switch(T1->balFactor) {
		case LH: rotateRL(T); return 2;
		case EH: rotateRR(T); return 1;
		case RH: rotateRR(T); return 2;
	}
	return 0;
}


int insertNode(AVLTree &T, TU tu) { 
	int res;
	if (T) { 
		if(stricmp(T->Key.tuAnh, tu.tuAnh) == 0) return 0; //da co trong tu dien
		if(stricmp(T->Key.tuAnh, tu.tuAnh) > 0) { 
			res = insertNode(T->pLeft, tu);
			if(res < 2) return res;
			switch(T->balFactor) { 
				case RH: T->balFactor = EH; return 1;
				case EH: T->balFactor = LH; return 2;
				case LH: balanceLeft(T); return 1;
			}
		}
		else { 
			res = insertNode(T->pRight, tu);
			if(res < 2) return res;
			switch(T->balFactor) { 
				case LH: T->balFactor = EH; return 1;
				case EH: T->balFactor = RH; return 2;
				case RH: balanceRight(T); return 1;
			}
		}
	}
	T = new AVLNode;
	if(T == NULL) 
		return -1; //thieu bo nho 
	T->Key = tu; 
	T->balFactor = EH;
	T->pLeft = T->pRight = NULL;
	return 2; // thanh cong, chieu cao tang	
}

int delNode(AVLTree &T, char tuAnh[]) { 
	int res;
	if(T==NULL) 
		return 0;
	if(stricmp(T->Key.tuAnh, tuAnh) > 0) {
		res = delNode(T->pLeft, tuAnh);
		if(res < 2) return res;
		switch(T->balFactor) { 
			case LH: T->balFactor = EH; return 2;
			case EH: T->balFactor = RH; return 1;
			case RH: return balanceRight(T); 
		}
	}
	if(stricmp(T->Key.tuAnh, tuAnh) < 0) { 
		res = delNode(T->pRight, tuAnh);
		if(res < 2) return res;
		switch(T->balFactor) { 
			case RH: T->balFactor = EH; return 2;
			case EH: T->balFactor = LH; return 1;
			case LH: return balanceLeft(T); 
		}
	}
	else { 
		AVLNode* p = T;
		if(T->pLeft == NULL) { 
			T = T->pRight; 
			res = 2; 
		}
		else if(T->pRight == NULL) { 
			T = T->pLeft; 
			res = 2; 
		}
		else { 
			res = searchStandFor(p,T->pRight);
			if(res < 2) return res;
			switch(T->balFactor) { 
				case RH: T->balFactor = EH; return 2;
				case EH: T->balFactor = LH; return 1;
				case LH: return balanceLeft(T); 
			}
			delete p; 
			return res;
		}
	}
}

int searchStandFor(AVLTree &p, AVLTree &q) { 
	int res;
	if(q->pLeft) { 
		res = searchStandFor(p, q->pLeft);
		if(res < 2) return res;
		switch(q->balFactor) { 
			case LH: q->balFactor = EH; return 2;
			case EH: q->balFactor = RH; return 1;
			case RH: return balanceRight(q); 
		}
	} else { 
		p->Key = q->Key; 
		p = q; 
		q = q->pRight; 
		return 2;
	}
}

void themTu(AVLTree &T) {
	TU tu;
	do {
		printf("Nhap tu can them: ");gets(tu.tuAnh);
		if(timKiem(T, tu.tuAnh) != NULL)
			printf("Tu nay da co trong tu dien. Vui long nhap lai!!!\n");
	} while(timKiem(T, tu.tuAnh) != NULL);
	printf("Nhap nghia cua tu can them: ");gets(tu.nghia);
	printf("Nhap vi du ve tu da them: ");gets(tu.vidu);
	if(insertNode(T, tu))
		printf("Them thanh cong.\n");
	else if(!insertNode(T, tu))
		printf("Tu nay da co san trong tu dien");
	else
		printf("Khong du bo nho luu tru.\n");
}

int suaTu(AVLTree &T, char tuAnh[]) {
	if(T == NULL)
		return -1;
	AVLNode* T1 = timKiem(T, tuAnh);
	if(T1) {
		printf("Nhap nghia cua tu: ");gets(T1->Key.nghia);
		printf("Nhap vi du ve tu: ");gets(T1->Key.vidu);
		return 1;
	}
	return 0;
}

void NLR(AVLTree T) {
	if(T != NULL) {
		printf("%s: %s. \nExample: %s\n", T->Key.tuAnh, T->Key.nghia, T->Key.vidu);
		NLR(T->pLeft);
		NLR(T->pRight);
	}
}

void LNR(AVLTree T){
	if(T != NULL){
		LNR(T->pLeft);
		printf("%s: %s. \nExample: %s\n", T->Key.tuAnh, T->Key.nghia, T->Key.vidu);
		LNR(T->pRight);
	}
}

void LRN(AVLTree T) {
	if(T != NULL) {
		LRN(T->pLeft);
		LRN(T->pRight);
		printf("%s: %s. \nExample: %s\n", T->Key.tuAnh, T->Key.nghia, T->Key.vidu);
	}
}


AVLNode* timKiem(AVLTree T, char tuAnh[]) {
	if(T == NULL) {
		return NULL;
	}	
	if(stricmp(T->Key.tuAnh, tuAnh) == 0)
		return T;
	return (stricmp(T->Key.tuAnh, tuAnh) > 0)?timKiem(T->pLeft, tuAnh):timKiem(T->pRight, tuAnh);
}

int tinhH(AVLTree T) {
	if(T == NULL) {
		return 0;
	}
	return tinhH(T->pLeft)>tinhH(T->pRight) ? tinhH(T->pLeft) + 1:tinhH(T->pRight) + 1;
}

void docFile(AVLTree &T1, char filename[], TU &x) {
	FILE *f = fopen(filename, "rb");
	if(f == NULL) {
		printf("Loi khong the doc file.\n");
		exit(0);
	}
	while(!feof(f)) {
		fread(&x, sizeof(TU), 1 ,f);
		if(!feof(f))
			insertNode(T1, x);
		else
			break;
	}
	printf("Doc thanh cong.\n");
	fclose(f);
}

void ghiFile(AVLTree T, char filename[]) {
	FILE *f = fopen(filename, "ab");
	if(f == NULL) {
		printf("Loi khong the doc file.\n");
		exit(0);
	}
	if(T!=NULL) {
		fwrite(&T->Key, sizeof(TU), 1, f);
		printf("Ghi thanh cong tu: %s.\n", T->Key.tuAnh);
//		fwrite(&t->Key.tuAnh, sizeof(TU), 1, f);
//		fwrite(&t->Key.nghia, sizeof(TU), 1, f);
//		fwrite(&t->Key.vidu, sizeof(TU), 1, f);
		ghiFile(T->pLeft, filename);
		ghiFile(T->pRight, filename);
	}
	fclose(f);
}

