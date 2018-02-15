#ifndef INCLUDED_CONNECTOR_H
#define INCLUDED_CONNECTOR_H

class Connector {
public:
	Connector();
	void pass_input_and_set_output(double input);
	void set_weight(double weight);
	void set_bias(double bias);
	void init_weight();
	//void init_bias();
	double get_weight();
	double get_bias();
	double get_output();
private:
	double m_weight;
	double m_weight_min;
	double m_weight_max;
	double m_bias;
	double m_bias_min;
	double m_bias_max;
	double m_output;
};

#endif // !INCLUDED_CONNECTOR_H
