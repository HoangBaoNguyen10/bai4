#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct HocPhan
{
	char maHP[30];
	char tenHP[30];
	int sotin;
	double DTL;
	double DCK;
	double DiemHP;
};

struct SinhVien
{
	char maSV[11];
	char hoDem[26];
	char tenSV[9];
	int namSinh;
	double diemKQ;
	HocPhan hocPhan[100];
	int soHocPhan;
};

typedef SinhVien Itemtype;

struct SNode
{
	Itemtype Info;
	SNode* Next;
};

SNode* createSNode(Itemtype x)
{
	SNode* p = new SNode;
	if (p == NULL)
	{
		printf("Khong the cap phat node moi!");
		_getch();
		return NULL;
	}
	p->Info = x;
	p->Next = NULL;
	return p;
}

void deleteSNode(SNode* p)
{
	if (p == NULL)
		return;
	p->Next = NULL;
	delete p;
}

struct SList
{
	SNode* Head;
	SNode* Tail;
};

void initSList(SList& sl)
{
	sl.Head = NULL;
	sl.Tail = NULL;
}

int isEmpty(SList sl)
{
	return sl.Head == NULL;
}

int insertTail(SList& sl, SNode* p)
{
	if (p == NULL)
		return 0;
	if (isEmpty(sl))
	{
		sl.Head = p;
		sl.Tail = p;
	}
	else
	{
		sl.Tail->Next = p;
		sl.Tail = p;
	}
	return 1;
}

// === Nhập & xuất ===

void nhapSinhVien(Itemtype& sv) 
{
	printf("\nNhap ma sinh vien: ");
	fgets(sv.maSV, sizeof(sv.maSV), stdin);
	sv.maSV[strcspn(sv.maSV, "\n")] = 0;

	printf("Nhap ho dem: ");
	fgets(sv.hoDem, sizeof(sv.hoDem), stdin);
	sv.hoDem[strcspn(sv.hoDem, "\n")] = 0;

	printf("Nhap ten sinh vien: ");
	fgets(sv.tenSV, sizeof(sv.tenSV), stdin);
	sv.tenSV[strcspn(sv.tenSV, "\n")] = 0;

	printf("Nhap nam sinh: ");
	scanf("%d", &sv.namSinh);
	getchar();
}

void nhapHocPhan(HocPhan& hp) 
{
	printf("Nhap ma hoc phan: ");
	fgets(hp.maHP, sizeof(hp.maHP), stdin);
	hp.maHP[strcspn(hp.maHP, "\n")] = 0;

	printf("Nhap ten hoc phan: ");
	fgets(hp.tenHP, sizeof(hp.tenHP), stdin);
	hp.tenHP[strcspn(hp.tenHP, "\n")] = 0;

	printf("Nhap so tin chi: ");
	scanf("%d", &hp.sotin);
	getchar();

	printf("Nhap diem thuong xuyen (DTL): ");
	scanf("%lf", &hp.DTL);
	getchar();

	printf("Nhap diem cuoi ky (DCK): ");
	scanf("%lf", &hp.DCK);
	getchar();

	hp.DiemHP = 0.3 * hp.DTL + 0.7 * hp.DCK;
}

void NhapThongTinSV(SList& ds) 
{
	int soSV, soMonHoc;
	printf("\nNhap so luong sinh vien: ");
	scanf("%d", &soSV);
	getchar();

	printf("Nhap so luong mon moi sinh vien phai hoc: ");
	scanf("%d", &soMonHoc);
	getchar();

	for (int i = 0; i < soSV; i++) {
		printf("\n=== Nhap thong tin sinh vien thu %d ===\n", i + 1);
		SinhVien sv;
		nhapSinhVien(sv);
		sv.soHocPhan = soMonHoc;

		for (int j = 0; j < soMonHoc; j++) {
			printf("\n--- Nhap hoc phan thu %d cho SV %s ---\n", j + 1, sv.maSV);
			nhapHocPhan(sv.hocPhan[j]);
		}

		SNode* p = createSNode(sv);
		insertTail(ds, p);
	}
}

void hienThiDanhSach(SList ds) 
{
	if (isEmpty(ds)) {
		printf("\nDanh sach rong!\n");
		return;
	}

	int stt = 1;
	for (SNode* p = ds.Head; p != NULL; p = p->Next) {
		SinhVien sv = p->Info;
		printf("\n--- Sinh vien %d ---\n", stt++);
		printf("Ma SV: %s\n", sv.maSV);
		printf("Ho dem: %s\n", sv.hoDem);
		printf("Ten: %s\n", sv.tenSV);
		printf("Nam sinh: %d\n", sv.namSinh);

		for (int i = 0; i < sv.soHocPhan; i++) {
			HocPhan hp = sv.hocPhan[i];
			printf("\t[%d] %s - %s | Tin chi: %d | DTL: %.2lf | DCK: %.2lf | DiemHP: %.2lf\n",
				i + 1, hp.maHP, hp.tenHP, hp.sotin, hp.DTL, hp.DCK, hp.DiemHP);
		}
	}
}
//cau a





// === Main ===
int main() 
{
	SList danhSach;
	initSList(danhSach);

	NhapThongTinSV(danhSach);

	printf("\n\n=== DANH SACH SINH VIEN ===\n");
	hienThiDanhSach(danhSach);

	return 0;
}
