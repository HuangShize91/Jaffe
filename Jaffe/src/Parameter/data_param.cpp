#include "data_param.h"

namespace jaffe {

	bool DPisleft(char c){
		return c == '{';
	}

	bool DPisright(char c){
		return c == '}';
	}

	bool JDataParam::SetParam(const vector<string> param){
		SetSharedParam(param);

		cout << "Initting Data Layer \"" << m_name << "\"..."
			<< endl;

		string line = "";
		vector<string> v_unique_param;
		bool b_enter = false;
		int i_left = 0;

		for (int i = 0; i < param.size(); i++){
			line = param.at(i);
			if (line.find(" data_param") != string::npos){
				b_enter = true;
				i_left += count_if(line.begin(), line.end(),
					DPisleft);
			}
			else if (b_enter){
				v_unique_param.push_back(line);
				i_left += count_if(line.begin(), line.end(),
					DPisleft);
				i_left -= count_if(line.begin(), line.end(),
					DPisright);
				if (i_left == 0){
					v_unique_param.pop_back();
					SetUniqueParam(v_unique_param);
					v_unique_param.clear();
					b_enter = false;
				}
			}
		}

		return true;
	}

	bool JDataParam::SetUniqueParam(const vector<string> param){
		string line = "";

		for (int i = 0; i < param.size(); i++){
			line = param.at(i);
			// 没有进入更深的参数
			matchString(line, "source:", &m_source);
			matchInt(line, "batch_size:", &m_batch_size);
			matchInt(line, "rank_skip:", &m_rank_skip);
			if (line.find("backend:") != string::npos){
				if (line.find("LEVELDB") != string::npos)
					m_backend = LEVELDB;
				else if (line.find("LMDB") != string::npos)
					m_backend = LMDB;
			}
			matchFloat(line, "scale:", &m_scale);
			matchString(line, "mean_file:", &m_mean_file);
			matchInt(line, "crop_size:", &m_crop_size);
			matchBool(line, "mirror:", &m_mirror);
			matchBool(line, "force_encoded_color:",
				&m_force_encoded_color);
			matchInt(line, "prefetch:", &m_prefetch);
		}
		cout << "Done" << endl;
		return true;

	}

	bool JDataParam::Show(){
		cout << endl;
		cout << "Data Layer (" << m_name << "):" << endl;
		ShowSharedParam();
		cout << "source: " << m_source << endl;
		cout << "batch_size: " << m_batch_size << endl;
		cout << "rank_skip: " << m_rank_skip << endl;
		cout << "backend: " << m_backend << endl;
		cout << "scale: " << m_scale << endl;
		cout << "mean_file: " << m_mean_file << endl;
		cout << "crop_size: " << m_crop_size << endl;
		cout << "mirror: " << m_mirror << endl;
		cout << "force_encode_color: " << m_force_encoded_color
			<< endl;
		cout << "prefetch: " << m_prefetch << endl;

		return true;
	}
}