#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tudien {
	char tuAnh[20];
	char nghia[20];
	char vidu[50];		
}TU;


typedef struct TNODE
{
	TU Key;
	struct TNODE *pLeft, *pRight;
} *TREE;

void themTu(TREE &t);
int ThemNut(TREE &t, TU tu);
void TaoCay(TREE &t);
void TaoCayTuMang(TREE &t, TU arr[], int n);
void NLR(TREE t);
void LNR(TREE t);
void LRN(TREE t);
int xoaTu(TREE &t, char tuAnh[]);
void xoaThayThe(TREE &t, TREE &q);
int tinhH(TREE t);
TREE timKiem(TREE T, char tuAnh[]);
int suaTu(TREE &t, char tuAnh[]);
void docFile(TREE &t1, char filename[], TU &x);
void ghiFile(TREE t, char filename[]);

int main(){
//	TREE t;
//	t = NULL;
//	char tu[20], tuUp[20], tuDel[20];
//	char c;
//	do {
//		fflush(stdin);
//		themTu(t);
//		printf("Tiep tuc them (y/n): ");scanf("%c", &c);
//	} while(c == 'y');
//	//Sua tu
//	fflush(stdin);
//	printf("Nhap tu can sua: ");gets(tuUp);
//	if(suaTu(t, tuUp))
//		printf("Sua thanh cong.\n");
//	else if(suaTu(t, tuUp) == 0)
//		printf("Tu khong ton tai.\n");
//	else
//		printf("Mang rong.\n");
//	//Xoa tu
//	printf("Nhap tu can xoa: ");gets(tuDel);
//	if(xoaTu(t, tuDel) == 0)
//		printf("Tu khong ton tai.\n");
//	else
//		printf("Xoa thanh cong.\n");
//		
//	//Xuat danh sach
//	LNR(t);
//	//Tim kiem tu
//	fflush(stdin);
//	printf("Nhap tu can tim kiem: ");gets(tu);
//	TREE t1 = timKiem(t, tu);
//	if(t1 == NULL)
//		printf("Tu khong ton tai!!!\n");
//	else {
//		printf("Tim thay:\n%s: %s.\nExample: %s\n", t1->Key.tuAnh, t1->Key.nghia, t1->Key.vidu);
//	}
//	//Ghi danh sach vao file
//	ghiFile(t, "T:/list.txt");
	TREE book;
	TU x;
	book = NULL;
	//Doc danh sach ra file
	docFile(book, "T:/list.txt", x);
	LNR(book);
}

int ThemNut(TREE &t, TU tu){
	if(t != NULL) {
		if(stricmp(t->Key.tuAnh, tu.tuAnh) == 0)
			return 0;
		else{
			if(stricmp(t->Key.tuAnh, tu.tuAnh) > 0)
				ThemNut(t->pLeft, tu);
			else
				ThemNut(t->pRight, tu);
		}
	}
	else {
		t = new TNODE;
		if(t == NULL)
			return -1;
		else {
			t->Key = tu;
			t->pLeft = t->pRight = NULL;
			return 1;	
		}
		
	}
}

void themTu(TREE &t) {
	TU tu;
	printf("Nhap tu can them: ");gets(tu.tuAnh);
	printf("Nhap nghia cua tu can them: ");gets(tu.nghia);
	printf("Nhap vi du ve tu da them: ");gets(tu.vidu);
	if(ThemNut(t, tu) == 1)
		printf("Them thanh cong.\n");
	else
		if(ThemNut(t, tu) == 0)
			printf("Tu nay da co san trong tu dien.\n");
		else
			printf("Khong du bo nho luu tru.\n");
}

int suaTu(TREE &t, char tuAnh[]) {
	if(t == NULL)
		return -1;
	TREE T = timKiem(t, tuAnh);
	if(T) {
		printf("Nhap nghia cua tu: ");gets(T->Key.nghia);
		printf("Nhap vi du ve tu: ");gets(T->Key.vidu);
		return 1;
	}
	return 0;
}

void NLR(TREE t) {
	if(t != NULL) {
		printf("%d\n", t->Key);
		NLR(t->pLeft);
		NLR(t->pRight);
	}
}

void LNR(TREE t){
	if(t != NULL){
		LNR(t->pLeft);
		printf("%s: %s. \nExample: %s\n", t->Key.tuAnh, t->Key.nghia, t->Key.vidu);
		LNR(t->pRight);
	}
}

void LRN(TREE t) {
	if(t != NULL) {
		LRN(t->pLeft);
		LRN(t->pRight);
		printf("%d\n", t->Key);
	}
}

int xoaTu(TREE &t, char tuAnh[]) {
	if(t == NULL)
		return 0;
	if(stricmp(t->Key.tuAnh, tuAnh) > 0)
		return xoaTu(t->pLeft, tuAnh);
	if(stricmp(t->Key.tuAnh, tuAnh) < 0)
		return xoaTu(t->pRight, tuAnh);
	TREE p = t;
	if(t->pLeft == NULL)
		t = t->pRight;
	else
		if(t->pRight == NULL)
			t = t->pLeft;
		else
			xoaThayThe(p, t->pRight);
	delete p;	
}

void xoaThayThe(TREE &t, TREE &q) {
	if(q->pLeft)
		xoaThayThe(t, q->pLeft);
	else {
		t->Key = q->Key;
		t = q;
		q = q->pRight;
	}
		
}

TREE timKiem(TREE T, char tuAnh[]) {
	if(T == NULL) {
		return NULL;
	}	
	if(stricmp(T->Key.tuAnh, tuAnh) == 0)
		return T;
	return (stricmp(T->Key.tuAnh, tuAnh) > 0)?timKiem(T->pLeft, tuAnh):timKiem(T->pRight, tuAnh);
}

int tinhH(TREE t) {
	if(t==NULL) {
		return 0;
	}
	return tinhH(t->pLeft)>tinhH(t->pRight) ? tinhH(t->pLeft) + 1:tinhH(t->pRight) + 1;
}

void docFile(TREE &t1, char filename[], TU &x) {
	FILE *f = fopen(filename, "rb");
	if(f == NULL) {
		printf("Loi khong the doc file.\n");
		exit(0);
	}
	while(!feof(f)) {
		fread(&x, sizeof(TU), 1 ,f);
		if(!feof(f))
			ThemNut(t1, x);
		else
			break;
	}
	printf("Doc thanh cong.\n");
	fclose(f);
}

void ghiFile(TREE t, char filename[]) {
	FILE *f = fopen(filename, "ab");
	if(f == NULL) {
		printf("Loi khong the doc file.\n");
		exit(0);
	}
	if(t!=NULL) {
		fwrite(&t->Key, sizeof(TU), 1, f);
//		fwrite(&t->Key.tuAnh, sizeof(TU), 1, f);
//		fwrite(&t->Key.nghia, sizeof(TU), 1, f);
//		fwrite(&t->Key.vidu, sizeof(TU), 1, f);
		ghiFile(t->pLeft, filename);
		ghiFile(t->pRight, filename);
	}
	printf("Ghi thanh cong.\n");
	fclose(f);
}

