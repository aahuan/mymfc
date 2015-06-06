
// mymfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mymfc.h"
#include "mymfcDlg.h"
#include "afxdialogex.h"
#include <list>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int IMAGE_WIDTH = 0;
int  IMAGE_HEIGHT = 0;



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	CPoint M_point;
	bool isDraw;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Cancel, &CAboutDlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CmymfcDlg �Ի���



CmymfcDlg::CmymfcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmymfcDlg::IDD, pParent)
	, TheImage(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmymfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmymfcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CmymfcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_EdgeDetect, &CmymfcDlg::OnBnClickedEdgedetect)
//	ON_BN_CLICKED(IDCANCEL, &CmymfcDlg::OnBnClickedCancel)
//	ON_BN_CLICKED(IDC_ReadImg, &CmymfcDlg::OnBnClickedReadimg)
	ON_BN_CLICKED(IDC_TRAIN, &CmymfcDlg::OnBnClickedTrain)
//	ON_BN_CLICKED(IDC_BUTTON1, &CmymfcDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_TEST, &CmymfcDlg::OnBnClickedTest)
ON_BN_CLICKED(IDC_BUTTON2, &CmymfcDlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_BUTTON1, &CmymfcDlg::OnBnClickedButton1)
ON_MESSAGE(WM_SYSTEMSET, OnMyMessage)
END_MESSAGE_MAP()


// CmymfcDlg ��Ϣ�������

BOOL CmymfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	CDC* pDC = GetDlgItem(IDC_ShowImg)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(IDC_ShowImg)->GetClientRect(&rect);
	IMAGE_WIDTH = rect.right - rect.left;			// ���ͼƬ�ؼ��Ŀ�͸�
	 IMAGE_HEIGHT = rect.bottom - rect.top;
	ReleaseDC(pDC);
	CvSize ImgSize;
	ImgSize.height = IMAGE_HEIGHT;
	ImgSize.width = IMAGE_WIDTH;
	TheImage = cvCreateImage(ImgSize, IPL_DEPTH_8U, IMAGE_CHANNELS);

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_CHECKED);

	//CProgressCtrl *pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	//pProgCtrl->SetRange(0, 100);//���ý�������Χ

	//pProgCtrl->SetStep(10);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CmymfcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmymfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();						// �ػ�Ի���
		CDialog::UpdateWindow();				// ����windows���ڣ�������ⲽ���ã�ͼƬ��ʾ�����������
		ShowImage(TheImage, IDC_ShowImg);		// �ػ�ͼƬ����
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmymfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CmymfcDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
// TODO: �����û��Զ�����Ϣ

		
		IplImage* ipl = cvLoadImage("D:\\1.bmp", 1);	// ��ȡͼƬ�����浽һ���ֲ����� ipl ��
		if (!ipl)									// �ж��Ƿ�ɹ���ȡͼƬ
			return 0;
		if (TheImage)								// ����һ����ʾ��ͼƬ��������
			cvZero(TheImage);

		ResizeImage(ipl, IDC_ShowImg);	// �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
		ShowImage(TheImage, IDC_ShowImg);			// ������ʾͼƬ����	
		cvReleaseImage(&ipl);
		return 0;
}


//�����ߵͶ�,��Ϊ�����Ǵ��ģʽ�洢��
void swapBuffer(char* buf)
{
	char temp;
	temp = *(buf);
	*buf = *(buf + 3);
	*(buf + 3) = temp;

	temp = *(buf + 1);
	*(buf + 1) = *(buf + 2);
	*(buf + 2) = temp;
}

//���ұ�Եsrcԭͼ��dst���ݱ�Ե�и��Сͼ��
void GetROI(Mat& src, Mat& dst)
{
	int left, right, top, bottom;
	left = src.cols;
	right = 0;
	top = src.rows;
	bottom = 0;

	//Get valid area
	for (int i = 0; i<src.rows; i++)
	{
		for (int j = 0; j<src.cols; j++)
		{
			if (src.at<uchar>(i, j) > 0)
			{
				if (j<left) left = j;
				if (j>right) right = j;
				if (i<top) top = i;
				if (i>bottom) bottom = i;
			}
		}
	}

	//Point center;
	//center.x = (left + right) / 2;
	//center.y = (top + bottom) / 2;

	int width = right - left;
	int height = bottom - top;
	int len = (width < height) ? height : width;

	//Create a squre
	dst = Mat::zeros(len, len, CV_8UC1);

	//Copy valid data to squre center
	Rect dstRect((len - width) / 2, (len - height) / 2, width, height);
	Rect srcRect(left, top, width, height);
	Mat dstROI = dst(dstRect);
	Mat srcROI = src(srcRect);
	srcROI.copyTo(dstROI);
}


int OpenFile(CString& fileName, CString& labelFileName){
	CFileDialog dlg(
		TRUE, _T("*.idx3-ubyte"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.idx3-ubyte)|*.idx3-ubyte"), NULL
		);										// ѡ��ͼƬ��Լ��
	dlg.m_ofn.lpstrTitle = _T("Open test Image");	// ���ļ��Ի���ı�����
	if (dlg.DoModal() != IDOK)					// �ж��Ƿ���ͼƬ
		return -1;

	fileName = dlg.GetPathName();			// ��ȡͼƬ·��

	CFileDialog dlg1(
		TRUE, _T("*.idx1-ubyte"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("label files (*.idx1-ubyte)|*.idx1-ubyte"), NULL
		);										// ѡ��ͼƬ��Լ��
	dlg1.m_ofn.lpstrTitle = _T("Open test Label");	// ���ļ��Ի���ı�����
	if (dlg1.DoModal() != IDOK)					// �ж��Ƿ���ͼƬ
		return -1;

	labelFileName = dlg1.GetPathName();			// ��ȡͼƬ·��
	return 0;
}


void CmymfcDlg::AddTestImgToDisplay(Mat dst){

	CDC* pDC = GetDlgItem(IDC_TESTIMG)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(IDC_TESTIMG)->GetClientRect(&rect);
	int rw = rect.right - rect.left;			// ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;
	ReleaseDC(pDC);
	Mat img = Mat::zeros(rh, rw, CV_8UC3);
	resize(dst, img, img.size());
	testImg.push_back(img);
}

//����MNIST���� flag 0:train  1:test
int CmymfcDlg::ReadTrainData(vector<NumTrainData>& buffer, int maxCount,int istrain)
{
	CString fileName;			// ��ȡͼƬ·��
	CString labelFileName;			// ��ȡͼƬ·��
	int flag = OpenFile(fileName, labelFileName);
	if (flag == -1){
		return -1;
	}

	ifstream lab_ifs(labelFileName, ios_base::binary);
	ifstream ifs(fileName, ios_base::binary);

	if (ifs.fail() == true)
		return -1;

	if (lab_ifs.fail() == true)
		return -1;

	//Read train data number and image rows / cols
	char magicNum[4], ccount[4], crows[4], ccols[4];
	ifs.read(magicNum, sizeof(magicNum));
	ifs.read(ccount, sizeof(ccount));
	ifs.read(crows, sizeof(crows));
	ifs.read(ccols, sizeof(ccols));

	int count, rows, cols;
	swapBuffer(ccount);
	swapBuffer(crows);
	swapBuffer(ccols);

	memcpy(&count, ccount, sizeof(count));
	memcpy(&rows, crows, sizeof(rows));
	memcpy(&cols, ccols, sizeof(cols));

	//Just skip label header
	lab_ifs.read(magicNum, sizeof(magicNum));
	lab_ifs.read(ccount, sizeof(ccount));

	//Create source and show image matrix
	Mat src = Mat::zeros(rows, cols, CV_8UC1);
	Mat temp = Mat::zeros(8, 8, CV_8UC1);
	Mat  dst;
	char label = 0;
	//Scalar templateColor(255, 0, 255);

	NumTrainData rtd;

	//int loop = 1000;
	int total = 0;

	while (!ifs.eof())
	{
		if (total >= count)
			break;
		total++;
		CString str;
		str.Format("���ڶ�ȡ�ļ���%d/%d", total, count);
		GetDlgItem(IDC_PTEXT)->SetWindowText(str);
		//Read label
		lab_ifs.read(&label, 1);
		label = label + '0';
		//Read source data
		ifs.read((char*)src.data, rows * cols);
		GetROI(src, dst);
		if (istrain == 1){
			AddTestImgToDisplay(dst);
		}
		rtd.result = label;
		resize(dst, temp, temp.size());
		for (int i = 0; i<8; i++)
		{
			for (int j = 0; j<8; j++)
			{
				rtd.data[i * 8 + j] = temp.at<uchar>(i, j);
			}
		}
		buffer.push_back(rtd);
		maxCount--;
		if (maxCount == 0)
			break;
	}
	if (istrain == 1){
		i = testImg.begin();
	}
	ifs.close();
	lab_ifs.close();
	return 0;
}

//train���ϵ����ݷֳ�image��label������
void CmymfcDlg::VectorToMatIAL(vector<NumTrainData>& trainData, Mat& data, Mat& res,string name){
	
	int testCount = trainData.size();
	Mat m = Mat::zeros(1, featureLen, CV_32FC1);
	data = Mat::zeros(testCount, featureLen, CV_32FC1);
	res = Mat::zeros(testCount, 1, CV_32SC1);

	for (int i = 0; i< testCount; i++)
	{

		NumTrainData td = trainData.at(i);
		if (name == "SVM"){
			memcpy(m.data, td.data, featureLen*sizeof(float));
			normalize(m, m);
			memcpy(data.data + i*featureLen*sizeof(float), m.data, featureLen*sizeof(float));
		}
		else memcpy(data.data + i*featureLen*sizeof(float), td.data, featureLen*sizeof(float));
		res.at<unsigned int>(i, 0) = td.result;
	}
}


//�������ɭ�֡���ѵ��
void CmymfcDlg::newRtStudy(vector<NumTrainData>& trainData)
{
	Mat data, res;
	VectorToMatIAL(trainData, data, res,"RT");
	/////////////START RT TRAINNING//////////////////
	CvRTrees forest;
	CvMat* var_importance = 0;

	forest.train(data, CV_ROW_SAMPLE, res, Mat(), Mat(), Mat(), Mat(),
		CvRTParams(10, 10, 0, false, 15, 0, true, 4, 100, 0.01f, CV_TERMCRIT_ITER));
	forest.save("new_rtrees.xml");
}

//֧��������--ѵ��
void CmymfcDlg::newSvmStudy(vector<NumTrainData>& trainData)
{
	Mat data, res;
	VectorToMatIAL(trainData, data, res,"SVM");

	/////////////START SVM TRAINNING//////////////////
	CvSVM svm;
	CvSVMParams param;
	CvTermCriteria criteria;

	criteria = cvTermCriteria(CV_TERMCRIT_EPS, 1000, FLT_EPSILON);
	param = CvSVMParams(CvSVM::C_SVC, CvSVM::RBF, 10.0, 8.0, 1.0, 10.0, 0.5, 0.1, NULL, criteria);

	svm.train(data, res, Mat(), Mat(), param);
	svm.save("SVM_DATA.xml");
}


//�������ɭ��Ԥ��
void CmymfcDlg::newRtPredict(vector<NumTrainData>& trainData)
{
	CvRTrees forest;
	forest.load("new_rtrees.xml");
	int right = 0;
	int error = 0;
	int total = 0;
	int testCount = trainData.size();

	Mat m = Mat::zeros(1, featureLen, CV_32FC1);
	for (int i = 0; i< testCount; i++)
	{

		NumTrainData td = trainData.at(i);
		memcpy(m.data, td.data, featureLen*sizeof(float));
		
		//normalize(m, m);
		char ret = (char)forest.predict(m);

		testLab.push_back(ret);

		char l = td.result;
		if (ret == l)
		{
			right++;
		}
		else
		{
			error++;
		}
		total++;
		CString str;
		str.Format("���ڲ������ݣ�%d/%d", total, testCount);
		GetDlgItem(IDC_PTEXT)->SetWindowText(str);
	}
	l = testLab.begin();
	CString string;
	string.Format("�ܹ���%d ��ȷ��%d ��ȷ�ʣ�%f", total, right, 100 * right / (float)total); //��������װ���ַ�����
	MessageBox(string, "����", MB_OKCANCEL);
}


//֧��������Ԥ��
void CmymfcDlg::newSvmPredict(vector<NumTrainData>& trainData)
{
	
	CvSVM svm;
	svm.load("SVM_DATA.xml");

	int right = 0;
	int error = 0;
	int total = 0;
	int testCount = trainData.size();

	Mat m = Mat::zeros(1, featureLen, CV_32FC1);
	for (int i = 0; i< testCount; i++)
	{

		NumTrainData td = trainData.at(i);
		memcpy(m.data, td.data, featureLen*sizeof(float));
		normalize(m, m);
		char ret = (char)svm.predict(m);
		testLab.push_back(ret);
		char l = td.result;
		if (ret == l)
		{
			right++;
		}
		else
		{
			error++;
		}
		total++;
		CString str;
		str.Format("���ڲ������ݣ�%d/%d", total, testCount);
		GetDlgItem(IDC_PTEXT)->SetWindowText(str);
	}
	l = testLab.begin();
	CString string;
	string.Format("�ܹ���%d ��ȷ��%d ��ȷ�ʣ�%f", total, right, 100*right/(float)total); //��������װ���ַ�����
	MessageBox(string, "����", MB_OKCANCEL);
}


int isContent(CvRect r1,CvRect r2){
	//�������
	if (r1.height == r2.height &&r1.width == r2.width && r1.x == r2.x && r1.y == r2.y){
		return 0;
	}
	//r1�������r2
	if (r1.x <= r2.x && r1.y<= r2.y && (r1.x + r1.width) >= (r2.x + r2.width) && (r1.y + r1.height) >= (r2.y + r2.height)){
		return  1;
	}
	//r2����r1
	if (r1.x >= r2.x && r1.y >= r2.y && (r1.x + r1.width) <= (r2.x + r2.width) && (r1.y + r1.height) <= (r2.y + r2.height)){
		return 2;
	}
	return 3;
}
//����Ե��ӵ�listrect�в���ֻ����������ͼ��
void addRect(CvRect rect,LISTRECT& listrect){
	int flag = 0;
	LISTRECT::iterator i ;
	bool flag_add = true;
	if (listrect.begin() == listrect.end()){
		listrect.push_back(rect);
	}
	else{
		
		for (i = listrect.begin(); i != listrect.end();){
			flag = isContent(*i, rect);
			if (flag == 3){
				flag_add =  true;
			}
			else if (flag == 2) {
				i=listrect.erase(i);
				flag_add = true;
				continue;
			}
			else if (flag == 1) {
				flag_add = false;
			}
			else if (flag == 0) {
				flag_add = false;
			}
			i++;
		}
		if (flag_add){
			listrect.push_back(rect);
		}
	}
}

//�ѱ�Ե���α��������
LISTRECT guiyihua(LISTRECT listrect){
	LISTRECT newlist;
	for each (Rect rect in listrect)
	{
		int h = rect.height > rect.width ? rect.height : rect.width;
		rect.x = rect.x - (h - rect.width) / 2;
		rect.y = rect.y - (h - rect.height) / 2;
		rect.height = h;
		rect.width = h;
		newlist.push_back(rect);
	}
	return newlist;
}


// ���ұ�Ե��������εı�Ե
// ����:   
// pBinary: �����ֵͼ�񣬵�ͨ����λ��IPL_DEPTH_8U��  
LISTRECT CmymfcDlg::FillInternalContours(IplImage *pBinary)
{
	CvSeq *pContour = NULL;
	CvSeq *pConInner = NULL;
	CvMemStorage *pStorage = NULL;
	LISTRECT listrect;
	// ִ������   
	if (pBinary)
	{
		// ������������   
		pStorage = cvCreateMemStorage(0);
		//cvFindContours(pBinary, pStorage, &pContour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_NONE);//��ȡ���еı�Ե����list��
		cvFindContours(pBinary, pStorage, &pContour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);//ֵ��ȡ������Ե
		// �����������   
		//cvDrawContours(pBinary, pContour, CV_RGB(255, 0, 255), CV_RGB(255, 0, 0), 2, CV_FILLED, 8, cvPoint(0, 0));

		// ������ѭ��   
		int wai = 0;
		int nei = 0;
		for (; pContour != NULL; pContour = pContour->h_next)
		{
			CvRect rect = cvBoundingRect(pContour, 0);
			//if( !(rect.x == rect.y && rect.x == 1)){
				//addRect(rect, listrect);
				listrect.push_back(rect);
			//}
			//cvRectangle(pBinary, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height), CV_RGB(0, 0, 255), 1, 8, 0);
		}
		//return listrect;
		
	}
	return guiyihua(listrect);
}


//����ѡ���ͼ��
void CmymfcDlg::OnBnClickedOk()
{

	CFileDialog dlg(
		TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg) |*.bmp; *.jpg | All Files (*.*) |*.*||"), NULL
		);										// ѡ��ͼƬ��Լ��
	dlg.m_ofn.lpstrTitle = _T("Open Image");	// ���ļ��Ի���ı�����
	if (dlg.DoModal() != IDOK)					// �ж��Ƿ���ͼƬ
		return;

	CString mPath = dlg.GetPathName();			// ��ȡͼƬ·��

	IplImage* ipl = cvLoadImage(mPath, 1);	// ��ȡͼƬ�����浽һ���ֲ����� ipl ��
	if (!ipl)									// �ж��Ƿ�ɹ���ȡͼƬ
		return;
	if (TheImage)								// ����һ����ʾ��ͼƬ��������
		cvZero(TheImage);

	ResizeImage(ipl, IDC_ShowImg);	// �Զ����ͼƬ�������ţ�ʹ��������ֵ�߸պõ��� 256���ٸ��Ƶ� TheImage ��
	ShowImage(TheImage, IDC_ShowImg);			// ������ʾͼƬ����	
	cvReleaseImage(&ipl);

}

//ֵָ���ؼ�����ʾͼ��
void CmymfcDlg::ShowImage(IplImage* img, UINT ID)	// ID ��Picture Control�ؼ���ID��
{
	CDC* pDC = GetDlgItem(ID)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;			// ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;
	int iw = img->width;						// ��ȡͼƬ�Ŀ�͸�
	int ih = img->height;
	int tx = (int)(rw - iw) / 2;					// ʹͼƬ����ʾλ�������ڿؼ�������
	int ty = (int)(rh - ih) / 2;
	SetRect(rect, tx, ty, tx + iw, ty + ih);

	CvvImage cimg;
	cimg.CopyOf(img);							// ����ͼƬ
	cimg.DrawToHDC(hDC, &rect);				// ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������

	ReleaseDC(pDC);
}

//�����ť������ʾ�ָ����Сͼ��
void CmymfcDlg::OnBnClickedEdgedetect()
{

	IplImage *gray = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	//edge = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	IplImage *bin = cvCreateImage(cvSize(IMAGE_WIDTH, IMAGE_HEIGHT), IPL_DEPTH_8U, 1);
	//int thresh = Otsu(TheImage);
	
	cvCvtColor(TheImage, gray, CV_BGR2GRAY);
	cvThreshold(gray, bin, 179, 255, CV_THRESH_BINARY);


	//��ȡͼƬ��һЩ����
	int height = bin->height;                     // ͼ��߶�
	int width = bin->width;                       // ͼ���ȣ�����Ϊ��λ��
	int step = bin->widthStep;                 // �����е�ͬ�е�֮����ֽ���
	uchar *data = (uchar *)bin->imageData;

	//��ɫ����
	for (int i = 0; i != height; ++i)
	{
		for (int j = 0; j != width; ++j)
		{
			data[i*step + j] = 255 - data[i*step + j];
		}
	}

	
	//cvCvtColor(edge, TheImage, CV_GRAY2BGR);
	ShowImage(bin, IDC_ShowImg);	
	// ������ʾͼƬ����
	IplImage *temp = cvCloneImage(bin);

	list<CvRect> CVRect = FillInternalContours(temp);//���ұ�Ե

	CDC* pDC = GetDlgItem(IDC_GRAYPIC)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����

	CRect rect;
	GetDlgItem(IDC_GRAYPIC)->GetClientRect(&rect);
	int rw = rect.right - rect.left;			// ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;
	ReleaseDC(pDC);
	int j = 0;
	CvSVM svm;
	svm.load("SVM_DATA.xml");
	GetDlgItem(IDC_RESULT)->SetWindowText("");
	for each (CvRect r in CVRect)
	{
		j++;
		cvSetImageROI(bin, r);
		IplImage *g = cvCloneImage(bin);
		IplImage* pDstImage = cvCreateImage(cvSize(rw, rh), g->depth, g->nChannels);
		cvResize(g, pDstImage);
		ShowImage(pDstImage, IDC_GRAYPIC);
		Mat dst = pDstImage;
		Mat temp = Mat::zeros(8, 8, CV_8UC1);
		Mat m = Mat::zeros(1, featureLen, CV_32FC1);
		resize(dst, temp, temp.size());
		for (int i = 0; i<8; i++)
		{
			for (int j = 0; j<8; j++)
			{
				m.at<float>(0, j + i * 8) = temp.at<uchar>(i, j);
			}
		}
		normalize(m, m);
		char ret = (char)svm.predict(m);
		CString s;
		s.Format("%d",ret-'0');
		GetDlgItem(IDC_NOWV)->SetWindowText(s);
		CString result;
		GetDlgItemText(IDC_RESULT, result);
		result = result +" "+ s;
		GetDlgItem(IDC_RESULT)->SetWindowText(result);
		cvResetImageROI(bin);
		cvReleaseImage(&pDstImage);
		cvReleaseImage(&g);
		Sleep(1000);
	}

	cvReleaseImage(&gray);
	cvReleaseImage(&bin);
	cvReleaseImage(&temp);

}

//����picture�ؼ���С����ͼƬ
void CmymfcDlg::ResizeImage(IplImage* img, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();		// �����ʾ�ؼ��� DC
	HDC hDC = pDC->GetSafeHdc();				// ��ȡ HDC(�豸���) �����л�ͼ����
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	int rw = rect.right - rect.left;			// ���ͼƬ�ؼ��Ŀ�͸�
	int rh = rect.bottom - rect.top;

	// ���� TheImage �� ROI ������������ͼƬ img
	cvSetImageROI(TheImage, cvRect(0, 0, rw, rh));

	// ��ͼƬ img �������ţ������뵽 TheImage ��
	cvResize(img, TheImage);

	// ���� TheImage �� ROI ׼��������һ��ͼƬ
	cvResetImageROI(TheImage);
}



//����ѵ��
void CmymfcDlg::OnBnClickedTrain()
{
	vector<NumTrainData> buffer;
	int flag;
	flag = ReadTrainData(buffer,60000,0);
	if (flag == -1){
		MessageBox("�ļ���ȡ�������¶�ȡ");
		return;
	}
	if (this->IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED){//����ɭ��ѡ��
		MessageBox("ѵ����ʼ");
		newRtStudy(buffer);
		MessageBox("ѵ������");
	}
	else{
		MessageBox("ѵ����ʼ");
		newSvmStudy(buffer);
		MessageBox("ѵ������");
	}
}



//���ݲ���
void CmymfcDlg::OnBnClickedTest()
{
	int flag;
	vector<NumTrainData> buffer;
	testImg.clear();
	testLab.clear();
	flag = CmymfcDlg::ReadTrainData( buffer,100,1);
	if (flag == -1){
		MessageBox("�ļ���ȡ�������¶�ȡ");
		return;
	}
	if (this->IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED){//����ɭ��ѡ��
		MessageBox("�����ļ���ȡ��ϣ�������ʼ����");
		GetDlgItem(IDC_PTEXT)->SetWindowText("����׼����������");
		newRtPredict(buffer);
	}
	else{
		MessageBox("�����ļ���ȡ��ϣ�������ʼ����");
		GetDlgItem(IDC_PTEXT)->SetWindowText("����׼����������");
		newSvmPredict(buffer);
	}
	buffer.empty();
}

//Ԥ������ͼ��
void CmymfcDlg::OnBnClickedButton2()
{
	list<Mat>::iterator i_end = testImg.end();
	if (!testImg.empty()){
		if (i != i_end){
			IplImage p = *i;
			ShowImage(&p, IDC_TESTIMG);
			CString str;
			str.Format("ϵͳʶ������֣�%d", *l - '0');
			GetDlgItem(IDC_TESTLABE)->SetWindowText(str);
			i++;
			l++;
		}
		else
		{
			MessageBox("��������Ԥ���ꡣ");
			return;
		}
	}
	else {
		MessageBox("��û�в��Խ����");
		return;
	}
}



void CmymfcDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CAboutDlg dlg;
	dlg.DoModal();

}


void CAboutDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CClientDC dc(this);
	CRect rect;
	CWnd *pWin = this;//��ȡ�ÿؼ���ָ�룬�Ϳ��ԶԸÿؼ�ֱ�Ӳ�����
	pWin->GetClientRect(rect);//�ѿؼ��ĳ����������Ϣ������rect��
	rect.top = rect.top + 50;
	HBITMAP hbitmap = CreateCompatibleBitmap(dc, rect.right - rect.left, rect.bottom - rect.top);
	//��������λͼ
	HDC hdc = CreateCompatibleDC(dc);      //��������DC���Ա㽫ͼ�񱣴�Ϊ��ͬ�ĸ�ʽ
	HBITMAP hOldMap = (HBITMAP)SelectObject(hdc, hbitmap);
	//��λͼѡ��DC�������淵��ֵ 
	BitBlt(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top, dc, 0, 0, SRCCOPY);
	//����ĻDC��ͼ���Ƶ��ڴ�DC��
	ATL::CImage image;
	image.Attach(hbitmap);                //��λͼת��Ϊһ��ͼ��
	HRESULT hResult = image.Save("D:\\1.bmp");     //����ͼ��
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}
	image.Detach();
	SelectObject(hdc, hOldMap);

	
	CWnd *pWnd = CWnd::FindWindow(NULL, _T("mymfc"));
	if (pWnd == NULL)
	{
		AfxMessageBox("���ճ���û������!");
		return;
	}

	pWnd->SendMessage(WM_SYSTEMSET, NULL, 0);
	CDialogEx::OnOK();
}


void CAboutDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CDialogEx::OnOK();
}


void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	CWnd *pWin = this;//��ȡ�ÿؼ���ָ�룬�Ϳ��ԶԸÿؼ�ֱ�Ӳ�����
	pWin->GetClientRect(rect);//�ѿؼ��ĳ����������Ϣ������rect��
	rect.bottom = rect.bottom - 50;
	if (rect.PtInRect(point)){
		isDraw = true;
		M_point = point;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	isDraw = false;
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	CWnd *pWin = this;//��ȡ�ÿؼ���ָ�룬�Ϳ��ԶԸÿؼ�ֱ�Ӳ�����
	pWin->GetClientRect(rect);//�ѿؼ��ĳ����������Ϣ������rect��
	rect.bottom = rect.bottom - 50;
	if (rect.PtInRect(point) && isDraw)
	{
		CDC *pDc = pWin->GetDC();//��ȡ�ÿؼ��Ļ���

		pDc->MoveTo(M_point);

		CPen newPen;       // ���ڴ����»���   
		CPen *pOldPen;     // ���ڴ�žɻ���   

		// ����ʵ�Ļ��ʣ��ֶ�Ϊ1����ɫΪ��ɫ   
		newPen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
		// ѡ���»��ʣ������ɻ��ʵ�ָ�뱣�浽pOldPen   
		pOldPen = pDc->SelectObject(&newPen);
		pDc->LineTo(point);
		ReleaseDC(pDc);
		M_point = point;
		// �ָ��ɻ���   
		pDc->SelectObject(pOldPen);
		// ɾ���»���   
		newPen.DeleteObject();

	}
	CDialogEx::OnMouseMove(nFlags, point);
}


BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	HCURSOR hCur = LoadCursor(NULL, IDC_CROSS);

::SetCursor(hCur);

return TRUE;

	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(rect);
	rect.bottom -= 50;
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����

	CDialog::OnPaint();

	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}
