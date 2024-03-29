// NODE.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"



using namespace std;
int main()
{
	node * NodeArray,*NodeOut;
	frame *FrameArray;
	char buff[100];
	int node_num;
	int sect_num;
	float g; 
	string posong, shear, alfa;
	int material_num;
	
	ifstream nodefile("c:\\node.csv");
	ifstream framefile("c:\\frame_connect.csv");
	ifstream slabfile("c:\\slab_connect.csv");
	ifstream slabsectfile("c:\\slab_sect.csv");
	ifstream frameloadfile("c:\\frame_load.csv");
	ifstream slabloadfile("c:\\slab_load.csv");
	ifstream materialfile("c:\\material.csv");
	ifstream framesectionfile("c:\\frame_sect.csv");
	ifstream framsectasignfile("c:\\frame_sect_assign.csv");
	ifstream slabsectassignfile("c:\\slab_sect_assign.csv");
	ifstream jointresrfile("C:\\joint_restr.CSV");
	ifstream nodemassfile("c:\\node_mass.csv");
	ofstream frameoutfile("c:\\frame_out.inp");
	ofstream nodeoutfile("c:\\node_out.inp");
	ofstream slaboutfile("c:\\slab_out.inp");
	ofstream slabsectoutfile("c:\\slab_sect_out.inp");
	ofstream frameloadoutfile("c:\\frame_load_out.inp");
	ofstream slabloadoutfile("c:\\slab_load_out.inp");

	ofstream modelfile("c:\\temp\\model_file.inp");
	modelfile << "*NODE,NSET=MODELNODESET"<<endl;
	string temp;
	string str;
	string p = ",";
	string Add_Node_Pre = "1000";
	string Slab_Pre = "100000";
	string Mass_Pre = "9000";
//	stringstream ss;

	if (!nodemassfile.is_open())
	{
		cout << "nodemass.csv file";
		exit(1);
	}
	if (!jointresrfile.is_open())
	{
		cout << "jointresrfile.csv file";
		exit(1);
	}

	if (!slabsectassignfile.is_open())
	{
		cout << "slabsectassignfile.csv file";
		exit(1);
	}
	if (!framsectasignfile.is_open())
	{
		cout << "frame_sect_assign.csv file";
		exit(1);
	}
	if (!nodefile.is_open())
	{
		cout << "Error open node.inp file";
		exit(1);
	}
	if (!framefile.is_open())
	{
		cout << "Error open frame.inp file";
		exit(1);
	}
	if (!frameoutfile.is_open())
	{
		cout << "Error open frame_out.inp file";
		exit(1);
	}
	if (!nodeoutfile.is_open())
	{
		cout << "Error open node_out.inp file";
		exit(1);
	}

	if (!slabfile.is_open())
	{
		cout << "Error open slab.inp file";
		exit(1);
	}
	if (!slaboutfile.is_open())
	{
		cout << "Error open slab_out.inp file";
		exit(1);
	}
	if (!slabsectfile.is_open())
	{
		cout << "Error open slab_sectfile.inp file";
		exit(1);
	}
	if (!slabsectoutfile.is_open())
	{
		cout << "Error open slab_sect_outfile.inp file";
		exit(1);
	}
	if (!frameloadoutfile.is_open())
	{
		cout << "Error open frame_load_out.inp file";
		exit(1);
	}
	if (!frameloadfile.is_open())
	{
		cout << "Error open frameloadfile.cvs file";
		exit(1);
	}
	if (!slabloadfile.is_open())
	{
		cout << "Error open slabloadfile.cvs file";
		exit(1);
	}
	if (!slabloadoutfile.is_open())
	{
		cout << "Error open slabloadoutfile.inp file";
		exit(1);
	}
	if (!framesectionfile.is_open())
	{
		cout << "Error open framsectionfile.csv file";
		exit(1);
	}


	//读取节点坐标
	node_num = 0;
	getline(nodefile, str);
	getline(nodefile, str);
	getline(nodefile, str);
	while (getline(nodefile, str))
	{
		string temp;

		str += p;
		node_num++;
		int i = 0;
		int pos;
		
		pos = str.find(p, i);
		temp = str.substr(i, pos - i);
		i = pos + 1;

		modelfile << temp << ",";

		for (int j = 0; j < 7; j++)
		{
			pos = str.find(p, i);
			i = pos + 1;
		}

		pos = str.find(p, i);
		temp = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << temp<<",";

		pos = str.find(p, i);
		temp = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << temp << ",";

		pos = str.find(p, i);
		temp = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << temp << endl;
	}
	
	
	
	//组成节点NodeArray
	
	nodefile.clear();
	nodefile.seekg(ios_base::beg);
	NodeArray = new node[node_num];
	node_num = 0;
	getline(nodefile, str);
	getline(nodefile, str);
	getline(nodefile, str);
	while (getline(nodefile,str))
	{
	//	nodefile.getline(buff, 100);
		
		
		string temp;
		double a, b, c, d;
		str += p;
		
		int i = 0;
		int pos;

		pos = str.find(p, i);
		a = atoi(str.substr(i, pos - i).c_str());
		i = pos + 1;

		

		for (int j = 0; j < 7; j++)
		{
			pos = str.find(p, i);
			i = pos + 1;
		}

		pos = str.find(p, i);
		b = atof(str.substr(i, pos - i).c_str());
		i = pos + 1;

		pos = str.find(p, i);
		c = atof(str.substr(i, pos - i).c_str());
		i = pos + 1;

		pos = str.find(p, i);
		d = atof(str.substr(i, pos - i).c_str());
		i = pos + 1;

		NodeArray[node_num] = node(a, b, c, d);
		node_num += 1;
			
		
		
	}
	//读取构件信息


	framefile.clear();
	framefile.seekg(ios::beg);
	getline(framefile, str);
	getline(framefile, str);
	getline(framefile, str);
	while (framefile>>str)
	{
		string temp;
		
			str += p;

			int i = 0;
			int pos, a, b, c;//a:构件编号，b：节点1，c：节点2

			pos = str.find(p, i);
			a = atoi(str.substr(i, pos - i).c_str());
			i = pos + 1;

			pos = str.find(p, i);
			b = atoi(str.substr(i, pos - i).c_str());
			i = pos + 1;

			pos = str.find(p, i);
			c = atoi(str.substr(i, pos - i).c_str());
			i = pos + 1;

			double x1, y1, z1, x2, y2, z2;
			for (int i = 0; i < node_num; i++)
			{
				bool  f1 = false;
				bool  f2 = false;
				if (NodeArray[i].NodeIndex == b)
				{
					x1 = NodeArray[i].x;
					y1 = NodeArray[i].y;
					z1 = NodeArray[i].z;
					f1 = true;
				}
				if (NodeArray[i].NodeIndex == c)
				{
					x2 = NodeArray[i].x;
					y2 = NodeArray[i].y;
					z2 = NodeArray[i].z;
					f2 = true;
				}
				if (f1&&f2) break;
			}

			node tempnode;
			if ((x1 == x2) && (y1 == y2))
			{

				tempnode.x = x1 - 1; tempnode.y = y1; tempnode.z = z1;
				tempnode.NodeIndex = a;
			}
			else 
				{
					tempnode.x = x1 + y1 - y2;
					tempnode.y = y1 + x2 - x1;
					tempnode.z = z1;
					tempnode.NodeIndex = a;
				}
			/*else if ((x1 == x2) && (z1 == z2))
			{
				tempnode.x = x1 - 1; tempnode.y = y1; tempnode.z = z1;
				tempnode.NodeIndex = a;
			}
			else if ((y1 == y2) && (z1 == z2))
			{
				tempnode.x = x1; tempnode.y = y1 - 1; tempnode.z = z1;
				tempnode.NodeIndex = a;
			}*/
/*			ss.str("");
			ss.clear();
			ss << Add_Node_Pre << a << "," << tempnode.x << "," << tempnode.y << "," << tempnode.z << endl;
			ss >> temp;
			nodeoutfile << temp << endl;
*/
			nodeoutfile<< Add_Node_Pre << a << "," << tempnode.x << "," << tempnode.y << "," << tempnode.z << endl;
/*
			ss.str("");
			ss.clear();
			ss << a << "," << b << "," << c << ","<<Add_Node_Pre << a;
			ss >> temp;
			frameoutfile << temp << endl;
			temp = "";
*/
			frameoutfile << a << "," << b << "," << c << "," << Add_Node_Pre << a << endl;
	}
	nodeoutfile.close(); frameoutfile.close();

	//写入附加节点信息

	modelfile << "**" << endl << "**" << "附加节点" << endl << "**" << endl << "*NODE" << endl;
	ifstream tempf;
	tempf.open("c:\\node_out.inp",ios_base::out );

	while (tempf>>temp)
	{
		modelfile << temp << endl;
	}
	tempf.close();

	//写入框架构件信息
	tempf.open("c:\\frame_out.inp", ios_base::out);
	modelfile << "**" << endl << "**框架单元" << endl << "**" << endl;
	modelfile << "**" << endl;
	modelfile << "*ELEMENT,TYPE=B31" << endl;
	while (tempf>>temp)
	{
		
		modelfile << temp << endl;
	}
	tempf.close();

	//壳单元信息

	modelfile << "**" << endl << "**壳单元" << endl << "**" << endl;
	modelfile << "*ELEMENT,TYPE=S4R" << endl;
	getline(slabfile, str);
	getline(slabfile, str);
	getline(slabfile, str);
	while (getline(slabfile, str))
	{
		string temp;

		str += p;

		int i = 0;
		int pos, a, b, c, d, e;//a:构件编号，b：节点1，c：节点2，d：节点3；e:节点4
		
		pos = str.find(p, i);
		a = atoi(str.substr(i, pos - i).c_str());
		i = pos + 1;

		pos = str.find(p, i);
		i = pos + 1;

		pos = str.find(p, i);
		b = atoi(str.substr(i, pos - i).c_str());
		i = pos + 1;

		pos = str.find(p, i);
		c = atoi(str.substr(i, pos - i).c_str());
		i = pos + 1;

		pos = str.find(p, i);
		d = atoi(str.substr(i, pos - i).c_str());
		i = pos + 1;

		pos = str.find(p, i);
		e = atoi(str.substr(i, pos - i).c_str());
		i = pos + 1;

		modelfile << Slab_Pre << a << "," << b << "," << c << "," << d << "," << e << endl;

		
	}

	modelfile << "**" << endl << "**材料" << endl << "**" << endl;

	getline(materialfile, str);
	getline(materialfile, str);
	getline(materialfile, str);
	while (getline(materialfile, str))
	{
		string name;
		string weight, density, elastic;
		str += p;

		int i = 0;
		int pos;

		pos = str.find(p, i);
		name = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << "*MATERIAL,NAME=" << name << endl;
		
		pos = str.find(p, i);
		weight= str.substr(i, pos - i);
		i = pos + 1;

		pos = str.find(p, i);
		density = str.substr(i, pos - i);

		
		g = atof(weight.c_str()) / atof(density.c_str());
		modelfile << "*DENSITY" << endl<<density << endl;

		i = pos + 1;
		pos = str.find(p, i);
		elastic = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << "*ELASTIC" << endl << elastic << ",";

		
		pos = str.find(p, i);
		shear = str.substr(i, pos - i);
		i = pos + 1;

		

		pos = str.find(p, i);
		posong = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << posong << endl;

		pos = str.find(p, i);
		alfa = str.substr(i, pos - i);
		i = pos + 1;

	}
	
	getline(framesectionfile,str);
	getline(framesectionfile, str);
	getline(framesectionfile, str);
	modelfile << "**" << endl << "**框架截面" << endl << "**" << endl;
	while (getline(framesectionfile, str))
	{
		
		string sect_name,material;
		float t3, t2;
		int num=0;
		str += p;

		int i = 0;
		int pos;
		pos = str.find(p, i);
		sect_name = str.substr(i, pos - i);
		modelfile << "*BEAM SECTION,ELSET=EL-" << sect_name << "," << endl;

		i = pos + 1;
		pos = str.find(p, i);
		material = str.substr(i, pos - i);
		modelfile << "MATERIAL=" << material << ",SECTION=RECT,ROTARY INERTIA=ISOTROPIC" << endl;

		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);
		t3 = atof(str.substr(i, pos - i).c_str());

		i = pos + 1;
		pos = str.find(p, i);
		t2 = atof(str.substr(i, pos - i).c_str());

		modelfile << t2 << "," << t3 << endl;
//		modelfile << "*TRANSVERSE SHEAR STIFFNESS" << endl << shear << "," << shear << endl;

	}
/*	while (slabsectfile >> str)
	{
		string temp;

		ss.str("");
		ss.clear();
		temp = "";
		ss << Slab_Pre << str << endl;
		ss >> temp;
		slabsectoutfile << temp << endl;



	}
	*/
	getline(slabsectfile, str);
	getline(slabsectfile, str);
	getline(slabsectfile, str);
	modelfile << "**" << endl << "**板截面" << endl << "**" << endl;
	while (getline(slabsectfile, str))
	{

		string sect_name, material;
		float thick;
		int num = 0;
		str += p;

		int i = 0;
		int pos;
		pos = str.find(p, i);
		sect_name = str.substr(i, pos - i);
		modelfile << "*SHELL SECTION,ELSET=EL-B-" << sect_name << "," << endl;

		i = pos + 1;
		pos = str.find(p, i);
		material = str.substr(i, pos - i);
		modelfile << "MATERIAL=" << material << endl;

		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);
		thick = atof(str.substr(i, pos - i).c_str());

		modelfile << thick << endl;
		modelfile << "**" << endl;

	}
	//
	//
	//框架截面集合
	//
	//
	getline(framsectasignfile, str);
	getline(framsectasignfile, str);
	getline(framsectasignfile, str);
	modelfile << "**" << endl << "**框架截面集合" << endl << "**" << endl;
   
	
	string old_sect_name;

	getline(framsectasignfile, str);
	str += p;
	
	int i = 0;
	int pos;
	pos = str.find(p, i);
	temp = str.substr(i, pos - i);

	i = pos + 1;
	pos = str.find(p, i);

	i = pos + 1;
	pos = str.find(p, i);

	i = pos + 1;
	pos = str.find(p, i);
	old_sect_name = str.substr(i, pos - i);

	modelfile << "*ELSET,ELSET=EL-" << old_sect_name << endl;
	modelfile << temp <<endl;
	
	while (getline(framsectasignfile, str))
	{

		string sect_name;
		int num = 0;
		str += p;

		int i = 0;
		int pos;
		pos = str.find(p, i);
		temp = str.substr(i, pos - i);
		
		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);

		i = pos + 1;
		pos = str.find(p, i);
		sect_name = str.substr(i, pos - i);
		if (sect_name == old_sect_name)
			modelfile << temp << endl;
		else
		{
			modelfile << "*ELSET,ELSET=EL-" << sect_name << endl;
			modelfile << temp << endl;
			old_sect_name = sect_name;
		}
	}
	//
	//
	//板截面集合
	//
	//
	getline(slabsectassignfile, str);
	getline(slabsectassignfile, str);
	getline(slabsectassignfile, str);
	modelfile << "**" << endl << "**板截面集合" << endl << "**" << endl;

	
	getline(slabsectassignfile, str);
	str += p;

	i = 0;
	pos = str.find(p, i);
	temp = str.substr(i, pos - i);

	
	i = pos + 1;
	pos = str.find(p, i);
	old_sect_name = str.substr(i, pos - i);

	modelfile << "*ELSET,ELSET=EL-B-" << old_sect_name << endl;
	modelfile << Slab_Pre << temp << endl;

	while (getline(slabsectassignfile, str))
	{

		string sect_name;
		int num = 0;
		str += p;

		int i = 0;
		int pos;
		pos = str.find(p, i);
		temp = str.substr(i, pos - i);

		
		i = pos + 1;
		pos = str.find(p, i);
		sect_name = str.substr(i, pos - i);
		if (sect_name == old_sect_name)
			modelfile << Slab_Pre << temp << endl;
		else
		{
			modelfile << "*ELSET,ELSET=EL-B" << sect_name << endl;
			modelfile << Slab_Pre << temp << endl;
			old_sect_name = sect_name;
		}

	}

	getline(jointresrfile, str);
	getline(jointresrfile, str);
	getline(jointresrfile, str);
	modelfile << "**" << endl << "**边界条件" << endl << "**" << endl;
	modelfile << "*BOUNDARY" << endl;
	string joint_res;
	while (getline(jointresrfile, str))
	{
		int num = 0;
		str += p;

		int i = 0;
		int pos;
		pos = str.find(p, i);
		temp = str.substr(i, pos - i);
		modelfile << temp << "," << "1,6"<<endl;
		joint_res += temp;
		joint_res += "\n";
	}
	modelfile << "**" << endl << "**" << endl;
	modelfile << "*NSET,NSET=N-RESTRAINT" << endl;
	modelfile << joint_res<<endl;

	getline(nodemassfile, str);
	getline(nodemassfile, str);
	getline(nodemassfile, str);
	node_num = 0;
	while (getline(nodemassfile, str))
	{
		node_num++;
	}
	nodemassfile.clear();
	nodemassfile.seekg(ios::beg);
	getline(nodemassfile, str);
	getline(nodemassfile, str);
	getline(nodemassfile, str);

	node_num = node_num - 3;

	while (node_num--)
	{
		getline(nodemassfile, str);
		string temp;
		str += p;

		int i = 0;
		int pos;
		string a, b;
		pos = str.find(p, i);
		a = str.substr(i, pos - i);
		i = pos + 1;
		modelfile << "*ELEMENT,TYPE=MASS,ELSET=N" << Mass_Pre << a << endl;
		modelfile << Mass_Pre << a << "," << a << endl;
		modelfile << "*MASS,ELSET=N" << Mass_Pre << a << endl;

		pos = str.find(p, i);
		i = pos + 1;

		pos = str.find(p, i);
		a = str.substr(i, pos - i);
		i = pos + 1;

		modelfile << a << endl;

	}

	modelfile << "*STEP,NAME=FRAME" << endl << "**" << endl;
	modelfile << "*STATIC" << endl << "1.,1.,1E-5,1." << endl;
	modelfile << "**" << endl;
	modelfile << "*DLOAD" << endl << ",GRAV," << g << ",0,0,-1" << endl;
	modelfile << "**"<<endl;

	modelfile << "*DLOAD" << endl;
	getline(frameloadfile, str);
	getline(frameloadfile, str);
	getline(frameloadfile, str);
	while (getline(frameloadfile, str))
	{
		string temp;

/*		ss.str("");
		ss.clear();
		temp = "";
		ss << str << endl;
*/
		str += p;
		int i = 0;
		int pos;
		string a, b;
		pos = str.find(p, i);

		a = str.substr(i, pos - i);
		i = pos + 1;

		for (int j = 0; j < 9; j++)
		{
			pos = str.find(p, i);
			i = pos + 1;
		}

		pos = str.find(p, i);
		b = str.substr(i, pos - i);
		i = pos + 1;

		temp = a + ",PZ,-" + b;
		frameloadoutfile << temp << endl;
		modelfile << temp << endl;

	}
	modelfile << "**" << endl;
	modelfile << "*DLOAD" << endl;
	getline(slabloadfile, str);
	getline(slabloadfile, str);
	getline(slabloadfile, str);
	while (getline(slabloadfile, str))
	{
		string temp;
		str += p;

		int i = 0;
		int pos;
		string a, b;
		pos = str.find(p, i);
		a = str.substr(i, pos - i);
		i = pos + 1;

		for (int j = 0; j < 3; j++)
		{
			pos = str.find(p, i);
			i = pos + 1;
		}

		pos = str.find(p, i);
		b = str.substr(i, pos - i);
		i = pos + 1;

		temp = Slab_Pre + a + ",P,-" + b;
		slabloadoutfile << temp << endl;
		modelfile << temp << endl;

	}

	modelfile << "**"<<endl;
	modelfile << "*OUTPUT,FIELD" << endl;
	modelfile << "*ELEMENT OUTPUT,DIRECTIONS=YES" << endl;
	modelfile << "E,S,SE,SF" << endl;
	modelfile << "*NODE OUTPUT" << endl;
	modelfile << "RF,U" << endl;
	modelfile << "**" << endl;
	modelfile << "*OUTPUT,HISTORY" << endl;
	modelfile << "*NODE OUTPUT,NSET=N-RESTRAINT" << endl;
	modelfile << "RF,U" << endl;
	modelfile << "*END STEP" << endl;



	modelfile<<"*STEP,name=Modes,perturbation"<<endl;
	modelfile << " *frequency, eigensolve = Lanczos" << endl;
	modelfile << "9, , , , ," << endl;
	modelfile << "*output, field" << endl;
	modelfile << "*NODE OUTPUT" << endl;
	modelfile << "U," << endl;
	modelfile << "*ELEMENT OUTPUT, directions = YES" << endl;
	modelfile << "SF," << endl;
	modelfile << "*END STEP" << endl;

    return 0;
}



node::node()
{
	x = 0.0;
	y = 0.0;
	NodeIndex = 0;
	z = 0.0;
}
node::node(int NodeIndex1,double x1, double y1,double z1)
{
	x = x1;
	y = y1;
	NodeIndex = NodeIndex1;

	z = z1;

}

node::~node()
{
}

