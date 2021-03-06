/*
 *
 *  Copyright (c) 2021
 *  name : Francis Banyikwa
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "batchfiledownloader.h"
#include "tabmanager.h"

#include <QFileDialog>

batchfiledownloader::batchfiledownloader()
{
}

void batchfiledownloader::init( settings * settings,Ui::MainWindow * ui,QWidget * parent )
{
	m_ui = ui ;
	m_settings = settings ;
	m_mainWindow = parent ;

	connect( m_ui->pbFileDownloaderQuit,&QPushButton::clicked,[](){

		tabManager::instance().basicDownloader().appQuit() ;
	} ) ;

	connect( m_ui->pbFileDownloaderDownload,&QPushButton::clicked,[ this ](){

		auto options = m_ui->lineEditFileOptions->text() ;

		auto url = m_ui->lineEditFileDownloader->text() ;

		tabManager::instance().basicDownloader().download( options,{ "-a",url } ) ;
	} ) ;

	m_ui->pbFileDownloaderFilePath->setIcon( [](){

		return QIcon( ":file" ) ;
	}() ) ;

	connect( m_ui->pbFileDownloaderFilePath,&QPushButton::clicked,[ this,parent ](){

		auto e = QFileDialog::getOpenFileName( parent,tr( "Set Batch File" ),QDir::homePath() ) ;

		if( !e.isEmpty() ){

			m_ui->lineEditFileDownloader->setText( e ) ;
		}
	} ) ;

	this->resetMenu() ;
}

void batchfiledownloader::init_done()
{
}

void batchfiledownloader::enableAll()
{
	m_ui->lineEditFileDownloader->setEnabled( true ) ;
	m_ui->lineEditFileOptions->setEnabled( true ) ;
	m_ui->pbFileDownloaderDownload->setEnabled( true ) ;
	m_ui->pbFileDownloaderFilePath->setEnabled( true ) ;
	m_ui->pbFileDownloaderOptions->setEnabled( true ) ;
	m_ui->pbFileDownloaderQuit->setEnabled( true ) ;
	m_ui->labelFileDownloader->setEnabled( true ) ;
	m_ui->labelFileDownloederPath->setEnabled( true ) ;
	m_ui->labelFileDownloederPathOptions->setEnabled( true ) ;
}

void batchfiledownloader::resetMenu()
{
	utility::setMenuOptions( m_settings,{},false,m_ui->pbFileDownloaderOptions,[ this ]( QAction * aa ){

		utility::selectedAction ac( aa ) ;

		if( ac.best() ){

			m_ui->lineEditFileOptions->setText( ac.bestText() ) ;
		}else{
			m_ui->lineEditFileOptions->setText( ac.objectName() ) ;
		}
	} ) ;
}

void batchfiledownloader::disableAll()
{
	m_ui->lineEditFileDownloader->setEnabled( false ) ;
	m_ui->lineEditFileOptions->setEnabled( false ) ;
	m_ui->pbFileDownloaderDownload->setEnabled( false ) ;
	m_ui->pbFileDownloaderFilePath->setEnabled( false ) ;
	m_ui->pbFileDownloaderOptions->setEnabled( false ) ;
	m_ui->pbFileDownloaderQuit->setEnabled( false ) ;
	m_ui->labelFileDownloader->setEnabled( false ) ;
	m_ui->labelFileDownloederPath->setEnabled( false ) ;
	m_ui->labelFileDownloederPathOptions->setEnabled( false ) ;
}

