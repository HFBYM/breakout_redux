# pragma once
template <tpyename T>
class Singleton
{
public:
	~Singleton();
	static T& get_instance() {
		static T instance;
		return instance;
	}

private:
	Singleton() = default;
	Singleton(const& Singleton) = delete;
};
