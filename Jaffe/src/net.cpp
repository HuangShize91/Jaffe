#include <iostream>
#include <fstream>

#include "Net.h"

using namespace std;


bool Net::Init(){	
	// 遍历所有 layer 的 type 参数，统计不同种类 layer 个数
	for(int i = 0; i < this->parameter->GetLayerNum(); i ++){
		Layer layer_param_temp;
		layer_param_temp.SetSharedParam(
			this->parameter->GetLayerParam(i));
		if(layer_param_temp.GetType() == "Data")
			this->data_layer_num ++;
		if (layer_param_temp.GetType() == "Convolution")
			this->conv_layer_num++;
	}

	// 为所有不同类型 layer 开辟内存空间
	this->conv_layers = new ConvolutionLayer[this->conv_layer_num];
	this->data_layers = new DataLayer[this->data_layer_num];
	
	// 分别设置所有 layer 的参数
	int conv_layer_idex = 0;
	int data_layer_idex = 0;
	for (int i = 0; i < this->parameter->GetLayerNum(); i++){
		Layer layer_param_temp;
		layer_param_temp.SetSharedParam(
			this->parameter->GetLayerParam(i));
		if (layer_param_temp.GetType() == "Data"){
			this->data_layers[data_layer_idex].SetParam(
				this->parameter->GetLayerParam(i));
			this->layers.push_back(
				&this->data_layers[data_layer_idex]);
			data_layer_idex++;
		}
		if (layer_param_temp.GetType() == "Convolution"){
			this->conv_layers[conv_layer_idex].SetParam(
				this->parameter->GetLayerParam(i));
			this->layers.push_back(
				&this->conv_layers[conv_layer_idex]);
			conv_layer_idex++;
		}
	}

	//this->layers.at(0)->Show();
	//this->layers.at(1)->Show();
	//this->layers.at(2)->Show();
	//this->layers.at(3)->Show();
	//this->layers.at(4)->Show();

	return  true;
}

bool Net::SetFilePath(const string filename){
	// 从文件中读取所有 layer 参数
	if (this->parameter->SetFilePath(filename))
		return true;

	return false;
}
