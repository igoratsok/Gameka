#include "welcomescreen.h"
#include "ui_welcomescreen.h"

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);


    ui->lineEdit->setText(QDir::homePath().append("/GamekaProjects"));

    QDomDocument doc("gameka_settings");
    QDomElement gameka_settings_xml = doc.createElement("gameka_settings");
    doc.appendChild(gameka_settings_xml);

    QDomElement directoryElement = doc.createElement("project_directory");
    directoryElement.setAttribute("path", ui->lineEdit->text());

    gameka_settings_xml.appendChild(directoryElement);

    QFile gameka_settings_file("gameka_settings.xml");
    gameka_settings_file.open(QIODevice::ReadWrite);

    QTextStream ts(&gameka_settings_file);
    ts << doc.toString();

    gameka_settings_file.close();










    populateProjectList();
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::setMainController(MainController *mainController)  {
    this->mainController = mainController;
}

void WelcomeScreen::on_buttonNewProject_pressed()
{
    openNewProjectWindow();
}


void WelcomeScreen::on_buttonLoadProject_pressed()
{
    QString fileName;
    FILE *fp;

    fileName = QString(ui->lineEdit->text()).append("/").append(currentProject).append("/").append("game.gmk");

    fp = fopen(fileName.toStdString().c_str(), "rb");

    if(!fp) {
        fileName = QString(ui->lineEdit->text()).append("/").append(currentProject).append("/").append("game.ldo");
    }

    if(!fileName.isEmpty()) {
        mainController->loadProject(fileName.toStdString());
    }


}

void WelcomeScreen::on_toolButtonProjectDirectory_pressed()
{
    QFileDialog *qFileDialog = new QFileDialog();
    QString directory = qFileDialog->getExistingDirectory();

    if(!directory.isEmpty()) {
        ui->lineEdit->setText(directory);
        populateProjectList();
    }

}

void WelcomeScreen::populateProjectList() {
    QStringList files;
    QDir dir = QDir(ui->lineEdit->text());

    ui->listWidget_2->clear();
    if(dir.exists()) {
        files = dir.entryList();


        for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
            QString file  = dir.absolutePath().append("/").append(((QString)*it));
            QDir projectDir = QDir(file);
            if(projectDir.exists()) {
                QStringList filters;
                filters << "game.gmk" << "game.ldo";

                std::cout << projectDir.entryList(filters).size() << std::endl;
                if(projectDir.entryList(filters).size() >= 1) {
                    ui->listWidget_2->addItem((QString)*it);
                }


            }

        }
    }

}

void WelcomeScreen::closeEvent(QCloseEvent *) {
    exit(0);
}


void WelcomeScreen::on_listWidget_2_itemActivated(QListWidgetItem *item)
{
    std::cout << "Teste" << std::endl;
}


void WelcomeScreen::on_listWidget_2_currentTextChanged(const QString &currentText)
{
    currentProject = currentText;
    ui->buttonLoadProject->setEnabled(true);
}

void WelcomeScreen::openNewProjectWindow() {
    mainController->openNewProjectWindow(ui->lineEdit->text(), this);
}

void WelcomeScreen::on_pushButtonUpdate_pressed()
{
    mainController->openUpdateManagerWindow();
}
