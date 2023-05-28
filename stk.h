#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_stk.h"
#include <QLabel>
#include <QmitkStdMultiWidget.h>
#include <mitkStandaloneDataStorage.h>
#include <mitkImage.h>
#include <mitkDataNode.h>
#include <itkImage.h>


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFiledialog>

#include <mitkIOUtil.h>
#include <QmitkDataStorageComboBox.h>
#include <QmitkDataStorageTreeModel.h>
#include "mitkProperties.h"
#include "mitkImageAccessByItk.h"
#include "mitkRenderingManager.h"
#include <itkOtsuThresholdImageFilter.h>

#include <vtkMarchingCubes.h>
class stk : public QMainWindow
{
    Q_OBJECT

public:
    stk(QWidget *parent = nullptr);
    ~stk();

public slots:
	void sltOpenFile();



private:
    Ui::stkClass ui;

	void CreateActions();
	void CreateMenus();

	QAction * openFileAction;
	QAction * exitAction;

	QLabel *label;
	QmitkStdMultiWidget *multiViewWgt;

	mitk::StandaloneDataStorage::Pointer m_DataStorage;
	mitk::Image::Pointer m_FirstImage;
	mitk::Image::Pointer m_ResultImage;
	mitk::DataNode::Pointer m_ResultNode;

};
