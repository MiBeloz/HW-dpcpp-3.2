#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class Observer;

class LogCommandWithObserver {
public:
    virtual ~LogCommandWithObserver() = default;

    void AddObserver(Observer* observer) noexcept {
	    m_observers.push_back(observer);
    }

    void RemoveObserver(Observer* observer) noexcept {
	    auto it = std::remove(m_observers.begin(), m_observers.end(), observer);
	    m_observers.erase(it, m_observers.end());
    }

    void warning(const std::string& message) const noexcept;

    void error(const std::string& message) const noexcept;

    void fatalError(const std::string& message) const noexcept;

private:
    std::vector<Observer*> m_observers;
};

class Observer {
public:
    explicit Observer(LogCommandWithObserver* logCommand) : mPtr_LogCommandWithObserver(logCommand) { mPtr_LogCommandWithObserver->AddObserver(this); }
    virtual ~Observer() { mPtr_LogCommandWithObserver->RemoveObserver(this); };
    virtual void onWarning(const std::string& message) const noexcept {}
    virtual void onError(const std::string& message) const noexcept {}
    virtual void onFatalError(const std::string& message) const noexcept {}

private:
    LogCommandWithObserver* mPtr_LogCommandWithObserver;
};

class Warning final : Observer {
public:
    explicit Warning(LogCommandWithObserver* logCommand) : Observer(logCommand) {}
    void onWarning(const std::string& message) const noexcept override {
	    std::cout << message << std::endl;
    }
};

class Error final : Observer {
public:
    explicit Error(LogCommandWithObserver* logCommand, const std::string& filename) : Observer(logCommand), m_filename(filename) {}
    void onError(const std::string& message) const noexcept override {
	    std::ofstream ofile;
	    ofile.open(m_filename, std::fstream::app);

	    if (ofile.is_open()) {
		    ofile << message << std::endl;
            std::cout << "Ошибка записана в файл '" + m_filename + "'." << std::endl;
	    }
	    ofile.close();
    }

private:
    std::string m_filename;
};

class FatalError final : Observer {
public:
    explicit FatalError(LogCommandWithObserver* logCommand, const std::string& filename) : Observer(logCommand), m_filename(filename) {}
    void onFatalError(const std::string& message) const noexcept override {
	    std::ofstream ofile;
	    ofile.open(m_filename, std::fstream::app);

	    if (ofile.is_open()) {
		    ofile << message << std::endl;
            std::cout << "Ошибка записана в файл '" + m_filename + "'." << std::endl;
	    }
	    ofile.close();

	    std::cout << message << std::endl;
    }

private:
    std::string m_filename;
};

inline void LogCommandWithObserver::warning(const std::string& message) const noexcept {
	    for (auto observer : m_observers) {
		    observer->onWarning(message);
	    }
}

inline void LogCommandWithObserver::error(const std::string& message) const noexcept {
    for (auto observer : m_observers) {
	    observer->onError(message);
	}
}

inline void LogCommandWithObserver::fatalError(const std::string& message) const noexcept {
    for (auto observer : m_observers) {
	    observer->onFatalError(message);
    }
}
