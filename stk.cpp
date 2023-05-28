#include "stk.h"

stk::stk(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	label = new QLabel("Seg Tool");
	QHBoxLayout * layout = new QHBoxLayout(this);;
	multiViewWgt = new QmitkStdMultiWidget;

	QWidget *centerWgt = new QWidget;
	layout->addWidget(multiViewWgt);

	centerWgt->setLayout(layout);
	this->setCentralWidget(centerWgt);
	//this->setLayout(layout);
	this->setMinimumSize(800, 600);

	m_DataStorage = mitk::StandaloneDataStorage::New();
	multiViewWgt->SetDataStorage(m_DataStorage);
	// Initialize bottom-right view as 3D view
	multiViewWgt->GetRenderWindow4()->GetRenderer()->SetMapperID(
		mitk::BaseRenderer::Standard3D);

	// Enable standard handler for levelwindow-slider
	multiViewWgt->EnableStandardLevelWindow();
	multiViewWgt->SetWidgetPlanesVisibility(true);
	multiViewWgt->DisableDepartmentLogo();

	CreateActions();
	CreateMenus();
	m_FirstImage = nullptr;
	m_ResultImage = nullptr;
	m_ResultNode = nullptr;

}

stk::~stk()
{}
void stk::CreateActions()
{
	openFileAction = new QAction(tr("&Open File"), this);
	exitAction = new QAction(tr("&Exit"), this);

	connect(openFileAction, SIGNAL(triggered()), this, SLOT(sltOpenFile()));

}

void stk::CreateMenus()
{
	QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(exitAction);

}

void stk::sltOpenFile()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);
	QStringList fileNames;
	if (dialog.exec())
		fileNames = dialog.selectedFiles();
	std::string fileName = fileNames[0].toStdString();

	mitk::StandaloneDataStorage::SetOfObjects::Pointer dataNodes;
	for (int i = 0; i < fileNames.length(); i++)
	{
		fileName = fileNames[i].toStdString();
		dataNodes = mitk::IOUtil::Load(fileName, *m_DataStorage);
	}
	if (dataNodes->empty())
	{
		fprintf(stderr, "Could not open file %s \n\n", fileName);
		exit(2);
	}

	mitk::Image::Pointer image = dynamic_cast<mitk::Image*> (dataNodes->at(0)->GetData());
	if ((m_FirstImage.IsNull()) && (image.IsNotNull()))
		m_FirstImage = image;

	multiViewWgt->ResetCrosshair();
	multiViewWgt->AddDisplayPlaneSubTree();
	multiViewWgt->AddPlanesToDataStorage();
}