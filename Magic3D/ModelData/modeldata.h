/*************************************************************************************
//
//  LICENSE INFORMATION
//
//  BCreator(tm)
//  Software for the control of the 3D Printer, "Creator"(tm)
//
//  Copyright 2011-2012 Creations, LLC
//  Creations(tm) and Creator(tm) are trademarks of Creations, LLC
//
//  This file is part of Creator
//
//    Creator is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Creator is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Creator .  If not, see <http://www.gnu.org/licenses/>.
//
//  The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
*************************************************************************************/
#ifndef MODELDATA_H
#define MODELDATA_H

#include <QString>
#include "../Interface/greentech.h"
#include "triangle3d.h"
#include "modelinstance.h"
#include <vector>
class GreenTech;
class aiScene;
class ModelData {
    friend class ModelInstance;
public:
    ModelData(GreenTech* main, bool bypassDisplayLists = false);
	~ModelData();
	
	QString GetFilePath();
	QString GetFileName();
    void clean(){normDispLists.clear();flippedDispLists.clear();triList.clear();instList.clear();}
	
	//data loading
	bool LoadIn(QString filepath); //returns success
	
	//instance
    ModelInstance* AddInstance();     //添加一个临时的模型
    int loadedcount;                    //模型的数量
	//render
    // the model can potentially own
    // multiply display lists, allowing
    // the graphics driver to better allocate
    // the memory needed for very large models.
    // these flipped  lists are generated when needed.
    // -Form functions are recursive
    std::vector<unsigned int> normDispLists;
    std::vector<unsigned int> flippedDispLists;

    bool FormFlippedDisplayLists();
    bool FormNormalDisplayLists();

    //geometry
    std::vector<Triangle3D> triList;                    //一个存储三角面的list
    QVector3D maxbound;                                 //Model的边界
	QVector3D minbound;

    std::vector<ModelInstance*> instList;             //临时模型列表，ModelInstance是本类的朋友类
   GreenTech* pMain;
   QString filepaths;//physical filepath
   QString filename;//filename (larry.stl)
private:	


	//utility
	void CenterModel();//called by loadin to adjust the model to have a center at 0,0,0
	
	const aiScene* pScene;

	//render

    int displaySkipping; //how many triangles to skip when rendering huge objects.
    bool bypassDispLists;
	
    int GetGLError();

};
#endif
