#include "loss_param.h"

namespace jaffe{

	bool JLossParam::SetParam(const vector<string> param){
		SetSharedParam(param);

		cout << "Initting loss layer \"" << m_name
			<< "\"..." << endl;

		string line = "";
		for (int i = 0; i < param.size(); i++){
			line = param.at(i);

			matchInt(line, "ignore_label:", &m_ignore_label);
			
			if (line.find("normalization:") != string::npos){
				if (line.find("FULL") != string::npos){
					m_normalization = FULL;
				}
				else if (line.find("BATCH_SIZE") != string::npos){
					m_normalization = BATCH_SIZE;
				}
				else if (line.find("NONE") != string::npos){
					m_normalization = NONE;
				}
			}

			matchBool(line, "normalize:", &m_normalize);
		}

		cout << "Done" << endl;
		return true;
	}
} // namespace jaffe