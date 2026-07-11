#ifndef CG_FORMAT_H
#define CG_FORMAT_H
#include <map>
#include <qstring.h>
#include <qbytearray.h>
namespace Format
{
	static std::map<QString, QString> pairmap(const char* data, const size_t size, char note = {})
	{
		std::map<QString, QString> map;
		for (size_t i = 0; i < size;)
		{
			char ch = data[i];
			if (note && ch == note)
			{
				for (; i < size && (data[i] != '\n' && data[i] != '\r' && data[i] != '\0'); i++);
				for (; i < size && (data[i] == '\n' || data[i] == '\r' || data[i] == '\0'); i++);
			}
			else if (ch != '\r' && ch != '\n' && ch != '\0')
			{
				const size_t key_begin = i;
				for (; i < size && (data[i] != '=' && data[i] != '\n' && data[i] != '\r' && data[i] != '\0'); i++);
				const size_t key_size = i - key_begin;

				if (data[i] != '=')
				{
					for (; i < size && (data[i] == '\n' || data[i] == '\r' || data[i] == '\0'); i++);
					continue;
				}

				i++;
				if (i >= size) break;

				const size_t val_begin = i;
				for (; i < size && (data[i] != '\n' && data[i] != '\r' && data[i] != '\0'); i++);
				const size_t val_size = i - val_begin;

				if (key_size && val_size) map.insert(std::make_pair(QString(QByteArray::fromRawData(&data[key_begin], key_size)), QString(QByteArray::fromRawData(&data[val_begin], val_size))));

				for (; i < size && (data[i] == '\n' || data[i] == '\r' || data[i] == '\0'); i++);
			}
			else
			{
				i++;
			}
		}
		return map;
	}
}
#endif