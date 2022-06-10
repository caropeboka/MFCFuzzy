
// MFCFuzzyDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCFuzzy.h"
#include "MFCFuzzyDlg.h"
#include "afxdialogex.h"
#include "CSeries.h"
#include "vector"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//========== INIT VARIABLE =============//
//Input Battery
int lowBattery[5]	= { 0,0,30,40,100};
int medbattery[5]	= { 30,40,60,70,100};
int highbattery[5]	= { 50,60,100,0,0 };
//int maxbattery[5]	= { 60,70,100,0,0 };

//Input RAM usage
int lowRam[5]		= {0,0,20,40,100};
int medRam[5]		= {20,40,60,80,100};
int highRam[5]		= {60,80,100,0,0};


//float hasil[4] = { waktu_sangatpendek[5],waktu_pendek[5],waktu_lumayan[5],waktu_lama[5] };

// CAboutDlg dialog used for App About

float LRam, MRam, HRam					// MF Fuzzi Set 1
, LBatt, MBatt, HBatt				// MF Fuzzi Set 2
, LBattLow, LBattMed, LBattHigh		//List Min Table
, MBattLow, MBattMed, MBattHigh		//List Min Table
, HBattLow, HBattMed, HBattHigh		//List Min Table
, lowPerformance, medPerformance, highPerformance;
//, uPanasCerah, uPanasSedang, uPanasMendung;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCFuzzyDlg dialog

CMFCFuzzyDlg::CMFCFuzzyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCFUZZY_DIALOG, pParent)
	//, m_chart1(0)
	//, m_chart2(0)
	, ec_battery(0)
	, ec_ram(0)
	, ec_lowbat(0)
	, ec_medbat(0)
	, ec_highbat(0)
	//, ec_upanas(0)
	, ec_lowram(0)
	, ec_medram(0)
	, ec_highram(0)
	//, m_chart3(0)
	//, m_chart4(0)
	, m_out1(_T(""))
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCFuzzyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_chart1);
	DDX_Control(pDX, IDC_TCHART2, m_chart2);
	DDX_Text(pDX, IDC_EDIT1, ec_battery);
	DDX_Text(pDX, IDC_EDIT2, ec_ram);
	DDX_Text(pDX, IDC_EDIT3, ec_lowbat);
	DDX_Text(pDX, IDC_EDIT4, ec_medbat);
	DDX_Text(pDX, IDC_EDIT5, ec_highbat);
	//DDX_Text(pDX, IDC_EDIT10, ec_upanas);
	DDX_Text(pDX, IDC_EDIT6, ec_lowram);
	DDX_Text(pDX, IDC_EDIT7, ec_medram);
	DDX_Text(pDX, IDC_EDIT8, ec_highram);
	DDX_Control(pDX, IDC_LIST1, lb_minrule);
	DDX_Control(pDX, IDC_LIST2, lb_maxrule);
	DDX_Control(pDX, IDC_TCHART3, m_chart3);
	DDX_Control(pDX, IDC_TCHART4, m_chart4);
	DDX_Control(pDX, IDC_LIST4, m_mfo1);
	DDX_Text(pDX, IDC_EDIT9, m_out1);
}

BEGIN_MESSAGE_MAP(CMFCFuzzyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCFuzzyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCFuzzyDlg::OnBnClickedEvaluasi)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCFuzzyDlg::OnBnClickedDefuzzifikasi)
END_MESSAGE_MAP()


// CMFCFuzzyDlg message handlers

BOOL CMFCFuzzyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Derajat Kotoran
	createFuzzy(1, 0, lowBattery);
	createFuzzy(1, 1, medbattery);
	//createFuzzy(1, 2, derajat_hangat);
	createFuzzy(1, 2, highbattery);

	//Jumlah Pakaian
	createFuzzy(2, 0, lowRam);
	createFuzzy(2, 1, medRam);
	createFuzzy(2, 2, highRam);

	//Output MF Speed
	for (i = 0; i <= 34; i++) m_c2[0][i] = 1;
	for (i = 35; i <= 45; i++) m_c2[0][i] = (45 - (float)i) / 10;
	for (i = 46; i <= 100; i++) m_c2[0][i] = 0;

	g = 25; jarak = 25; h = 50;
	for (i = 0; i <= 24; i++) m_c2[1][i] = 0;
	for (i = 25; i <= 75; i++) m_c2[1][i] = 1 - (2 * fabs((float)(i - g - jarak)) / h);
	for (i = 76; i <= 100; i++) m_c2[1][i] = 0;

	g = 10; jarak = 40; h = 20;
	//for (i = 0; i <= 39; i++) m_c2[2][i] = 0;
	//for (i = 40; i <= 60; i++) m_c2[2][i] = 1 - (2 * fabs((float)(i - g - jarak)) / h);
	//for (i = 61; i <= 100; i++) m_c2[2][i] = 0;

	for (i = 0; i <= 54; i++) m_c2[2][i] = 0;
	for (i = 55; i <= 65; i++) m_c2[2][i] = (10 - (65 - (float)i)) / 10;
	for (i = 66; i <= 100; i++) m_c2[2][i] = 1;

	for (j = 0; j < 3; j++) {
		for (i = 0; i <= 100; i++) {
			((CSeries)(m_chart3.Series(j))).AddXY(i, m_c2[j][i], NULL, 536870912);
		}
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCFuzzyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCFuzzyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCFuzzyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCFuzzyDlg::createFuzzy(int mode, int index, int input[5]) {
	unsigned long color = 536870912;
	if (mode == 1) {
		((CSeries)m_chart1.Series(index)).AddXY(input[0], 0, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[1], 1, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[2], 1, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[3], 0, NULL, color);
		((CSeries)m_chart1.Series(index)).AddXY(input[4], 0, NULL, color);
	}

	
	else if (mode == 2) {
		((CSeries)m_chart2.Series(index)).AddXY(input[0], 0, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[1], 1, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[2], 1, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[3], 0, NULL, color);
		((CSeries)m_chart2.Series(index)).AddXY(input[4], 0, NULL, color);
	}
}

float fuzzifikasi(int input, int rule[5]) {
	float output;
	float finput = (float)input;

	if (finput < rule[0])
		output = 0;
	else if (finput >= rule[0] && finput < rule[1]) {
		if (rule[1] - rule[0] == 0.0)
			output = 1;
		else
			output = (finput - rule[0]) / (rule[1] - rule[0]);
	}
	else if (finput >= rule[1] && finput <= rule[2]) {
		output = 1;
	}
	else if (finput >= rule[2] && finput <= rule[3]) {
		if (rule[3] - rule[2] == 0.0)
			output = 0;
		else
			output = (rule[3] - finput) / (rule[3] - rule[2]);
	}
	else if (finput > rule[3])
		output = 0;

	return output;
}

float minf(float a, float b) {
	if (a <= b)
		return a;
	else
		return b;
}

float maxf(float a, float b) {
	if (a >= b)
		return a;
	else
		return b;
}

float maxOfArr(float asd[], int length) {

	float maxV = 0;
	for (int i = 0; i < length; i++) {
		if (asd[i] > maxV) {
			maxV = asd[i];
		}
	}
	return maxV;
}


void CMFCFuzzyDlg::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here
	UpdateData(true);

	((CSeries)m_chart1.get_aSeries(4)).Clear();
	((CSeries)m_chart1.get_aSeries(4)).AddXY(ec_battery, 0, NULL, 536870912);
	((CSeries)m_chart1.get_aSeries(4)).AddXY(ec_battery, 1, NULL, 536870912);
	((CSeries)m_chart1.get_aSeries(4)).AddXY(ec_battery, 0, NULL, 536870912);
	((CSeries)m_chart2.get_aSeries(3)).Clear();
	((CSeries)m_chart2.get_aSeries(3)).AddXY(ec_ram, 0, NULL, 536870912);
	((CSeries)m_chart2.get_aSeries(3)).AddXY(ec_ram, 1, NULL, 536870912);
	((CSeries)m_chart2.get_aSeries(3)).AddXY(ec_ram, 0, NULL, 536870912);

	//Proses Fuzzifikasi
	ec_lowbat = LRam = fuzzifikasi(ec_battery, lowBattery);
	ec_medbat = MRam = fuzzifikasi(ec_battery, medbattery);
	ec_highbat = HRam = fuzzifikasi(ec_battery, highbattery);
	//ec_upanas = uPanas = fuzzifikasi(ec_battery, highbattery);

	ec_lowram = LBatt = fuzzifikasi(ec_ram, lowRam);
	ec_medram = MBatt = fuzzifikasi(ec_ram, medRam);
	ec_highram = HBatt = fuzzifikasi(ec_ram, highRam);
		
	UpdateData(false);
}


void CMFCFuzzyDlg::OnBnClickedEvaluasi()
{
	
	// TODO: Add your control notification handler code here
	//Proses Rule Evaluation
	// EVALUASI
	UpdateData(true);

	CString str = _T("");
	while (lb_minrule.GetCount() > 0) lb_minrule.DeleteString(0);
	while (lb_maxrule.GetCount() > 0) lb_maxrule.DeleteString(0);

	//Min rule
	LBattLow = minf(HRam, LBatt);
	LBattMed = minf(HRam, MBatt);
	LBattHigh = minf(HRam, HBatt);

	MBattLow = minf(MRam, LBatt);
	MBattMed = minf(MRam, MBatt);
	MBattHigh = minf(MRam, HBatt);

	HBattLow = minf(LRam, LBatt);
	HBattMed = minf(LRam, MBatt);
	HBattHigh = minf(LRam, HBatt);

	//uPanasCerah = minf(uPanas, uCerah);
	//uPanasSedang = minf(uPanas, uSedang);
	//uPanasMendung = minf(uPanas, uMendung);


	str.Format(_T("HBattLow = %.3f"), LBattLow); lb_minrule.AddString(str);
	str.Format(_T("HBattMed = %.3f"), LBattMed); lb_minrule.AddString(str);
	str.Format(_T("HBattHigh = %.3f"), LBattHigh); lb_minrule.AddString(str);

	str.Format(_T("MBattLow = %.3f"), MBattLow); lb_minrule.AddString(str);
	str.Format(_T("MBattMed = %.3f"), MBattMed); lb_minrule.AddString(str);
	str.Format(_T("MBattHigh = %.3f"), MBattHigh); lb_minrule.AddString(str);

	str.Format(_T("LBattLow = %.3f"), HBattLow); lb_minrule.AddString(str);
	str.Format(_T("LBattMed = %.3f"), HBattMed); lb_minrule.AddString(str);
	str.Format(_T("LBattHigh = %.3f"), HBattHigh); lb_minrule.AddString(str);

	//str.Format(_T("uPanasCerah = %.3f"), uPanasCerah); lb_minrule.AddString(str);
	//str.Format(_T("uPanasSedang = %.3f"), uPanasSedang); lb_minrule.AddString(str);
	//str.Format(_T("uPanasMendung = %.3f"), uPanasMendung); lb_minrule.AddString(str);

	//Max Rule
	highPerformance = maxf(maxf(LBattHigh, MBattHigh), HBattHigh);
	str.Format(_T("highPerformance = %.3f"), highPerformance); lb_maxrule.AddString(str);
	medPerformance = maxf(maxf(LBattMed, MBattMed), HBattMed);
	str.Format(_T("medPerformance = %.3f"), medPerformance); lb_maxrule.AddString(str);
	lowPerformance = maxf(maxf(LBattLow, MBattLow), HBattLow);
	str.Format(_T("lowPerformance = %.3f"), lowPerformance); lb_maxrule.AddString(str);
	//highPerformanceest = uPanasCerah;
	//str.Format(_T("highPerformanceest = %.3f"), highPerformanceest); lb_maxrule.AddString(str);

	UpdateData(false);
}


void CMFCFuzzyDlg::OnBnClickedDefuzzifikasi()
{
	// TODO: Add your control notification handler code here
	//Proses Defuzzifikasi
	UpdateData(true);
	thresh1[0] = lowPerformance;
	thresh1[1] = medPerformance;
	thresh1[2] = highPerformance;
	//thresh1[3] = highPerformanceest;

	CString mfformat;
	std::vector<CString> row;
	m_mfo1.ResetContent();
	((CSeries)(m_chart4.Series(0))).Clear();

	float ax[101][4], bx[101], cx[4], dx;

	float num = 0, denum = 0, coa = 0;

	for (i = 0; i < 3; i++) {
		for (j = 0; j <= 100; j++) {
			ax[j][i] = std::fmin(m_c2[i][j], thresh1[i]);
		}
	}
	for (i = 0; i <= 100; i++) {
		bx[i] = maxOfArr(ax[i], 3);
		num += (bx[i] * i);
		denum += bx[i];
	}
	coa = num / denum;
	for (i = 0; i <= 100; i++) {
		((CSeries)(m_chart4.Series(0))).AddXY(i, bx[i], NULL, 536870912);// Menggambar Titik Potong
	}

	((CSeries)m_chart4.get_aSeries(1)).Clear();
	((CSeries)m_chart4.get_aSeries(1)).AddXY(coa, 0, NULL, 536870912);
	((CSeries)m_chart4.get_aSeries(1)).AddXY(coa, 1, NULL, 536870912);
	((CSeries)m_chart4.get_aSeries(1)).AddXY(coa, 0, NULL, 536870912);


	row.push_back(L"lowPerformance");
	row.push_back(L"medPerformance");
	row.push_back(L"highPerformance");
	//row.push_back(L"highPerformanceest");

	for (i = 0; i < 3; i++) {
		mfformat.Format(L"%d) %s = %f", i + 1, row[i], m_c2[i][int(coa)]);
		m_mfo1.AddString(mfformat);
		cx[i] = m_c2[i][int(coa)];
	}

	UpdateData(false);

	dx = maxOfArr(cx, 3);
	for (i = 0; i < 3; i++) {
		if (dx == cx[i]) {
			mfformat.Format(L"%s %f", row[i], coa);
			SetDlgItemText(IDC_EDIT9, mfformat);
		}
	}
}
