#pragma once

#include <boost/python.hpp>
#include <boost/iostreams/stream.hpp>

/**
 * @brief The PythonInputDevice class is a helper class to construct an istream from an python object.
 *        This object must be extend the BaseIO class from python.
 */
class PythonInputDevice : public boost::iostreams::source
{
public:
    /**
     * @brief PythonInputDevice construct a reader from a python object.
     * @param object The BaseIO object from python.
     */
    explicit PythonInputDevice(boost::python::object object)
        : object_(object) {

    }

    /**
     * @brief #read read the buffer and write it into the buffer.
     * @param buffer The buffer to write the data into.
     * @param buffer_size the size of the buffer.
     * @return The readed data size.
     */
    std::streamsize read(char_type* buffer, std::streamsize buffer_size)
    {
        namespace python = boost::python;
        boost::python::object py_data = object_.attr("read")(buffer_size);
        std::string data = python::extract<std::string>(py_data);
        if (data.empty()) {
            return -1;
        }

        copy(data.begin(), data.end(), buffer);
        return data.size();
  }

private:
    boost::python::object object_;
};

/**
 * @brief The PythonOutputDevice class is a helper class to construct an ostream from an python object.
 *        This object must be extend the BaseIO class from python.
 */
class PythonOutputDevice : public boost::iostreams::sink
{
public:
    typedef char char_type;
    struct category : boost::iostreams::sink_tag, boost::iostreams::flushable_tag {};

    /**
     * @brief PythonOutputDevice construct a writer from a python object.
     * @param object The BaseIO object from python.
     */
    explicit PythonOutputDevice(boost::python::object object) : object_(object) {
    }

    /**
     * @brief #write Write the data to python by the given buffer and its size.
     * @param buffer The data to write.
     * @param buffer_size The size of the data to write.
     * @return The writen data size.
     */
    std::streamsize write(const char* buffer, std::streamsize buffer_size) {
        namespace python = boost::python;
        python::str data(buffer, buffer_size);
        python::extract<std::streamsize> bytes_written(object_.attr("write")(data));
        return bytes_written.check() ? bytes_written : buffer_size;
    }

    /**
     * @brief #flush Flush the stream to ensure all data gets written.
     * @return True if the data gets flushed successfully.
     */
    bool flush() {
        boost::python::object flush = object_.attr("flush");
        if (!flush.is_none()) {
            flush();
        }
        return true;
    }

private:
    boost::python::object object_;
};
