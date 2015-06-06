
// mymfcDlg.h : ͷ�ļ�
//

#pragma once


// CmymfcDlg �Ի���
class CmymfcDlg : public CDialogEx
{
// ����
public:
	CmymfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	IplImage* TheImage;//��ɫͼ��
	list<Mat> testImg;
	list<char> testLab;
	list<Mat>::iterator i;
	list<char>::iterator l;

	afx_msg void OnBnClickedOk();
	void ShowImage(IplImage* img, UINT ID);
	int  newTestFile(vector<Mat>& Img, vector<char>& Lable);
	void ResizeImage(IplImage* img, UINT ID);
	afx_msg void OnBnClickedEdgedetect();
	afx_msg void OnBnClickedTrain();
	afx_msg void OnBnClickedTest();
	void VectorToMatIAL(vector<NumTrainData>& trainData, Mat& data, Mat& res,string name);
	void newRtStudy(vector<NumTrainData>& trainData);
	void newSvmStudy(vector<NumTrainData>& trainData);
	int ReadTrainData(vector<NumTrainData>& buffer, int maxCount, int istrain);
	void newRtPredict(vector<NumTrainData>& trainData);
	void newSvmPredict(vector<NumTrainData>& trainData);
	LISTRECT FillInternalContours(IplImage *pBinary);
	void CmymfcDlg::AddTestImgToDisplay(Mat dst);
	afx_msg void OnBnClickedButton2();
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton1();
};
