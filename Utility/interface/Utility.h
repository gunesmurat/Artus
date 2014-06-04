
#pragma once

#include <map>
#include <type_traits>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include "Artus/Core/interface/Cpp11Support.h"

namespace Utility {

	template<typename Enum>
	using enableEnumType = typename std::enable_if< std::is_enum<Enum>::value, typename std::underlying_type<Enum>::type>::type;

	// convert enum class type to underlying (int) value
	template<typename Enum>
	constexpr inline enableEnumType<Enum> ToUnderlyingValue(Enum e) noexcept
	{
		return static_cast<typename std::underlying_type<Enum>::type>(e);
	}

	// convert underlying (int) value to enum class type
	template< typename Enum , typename T>
	constexpr inline typename std::enable_if<std::is_enum<Enum>::value && std::is_integral<T>::value, Enum>::type ToEnum(T value) noexcept
	{
		return static_cast<Enum>( value );
	}

	std::string ReadStringFromFile(std::string fileName);

	// parse vector of strings into map of strings by splitting keys and values by the delimiters
	std::map<std::string, std::vector<std::string> > ParseVectorToMap(std::vector<std::string> const& vectorToParse,
	                                                                  std::string const& delimiters=":");
	
	// convert string map into other type by using boost::lexical_cast
	template<class TKey, class TValue>
	std::map<TKey, std::vector<TValue> > ParseMapTypes(std::map<std::string, std::vector<std::string> > const& inputMap,
	                                                   std::map<std::string, std::vector<TValue> > & outputMapWrongTKey,
	                                                   std::map<TKey, std::vector<std::string> > & outputMapWrongTValue,
	                                                   std::map<std::string, std::vector<std::string> > & outputMapWrongTKeyWrongTValue)
	{
		std::map<TKey, std::vector<TValue> > outputMap;
		
		
		for (std::map<std::string, std::vector<std::string> >::const_iterator inputItem = inputMap.begin();
		     inputItem != inputMap.end(); ++inputItem)
		{
			// parse key
			TKey key;
			bool keyParsed = true;
			try {
				key = boost::lexical_cast<TKey>(inputItem->first);
			}
			catch (boost::bad_lexical_cast const& exception) {
				keyParsed = false;
			}
			
			for (std::vector<std::string>::const_iterator inputValueItem = inputItem->second.begin();
			     inputValueItem != inputItem->second.end(); ++inputValueItem)
			{
				// parse value
				TValue valueItem;
				bool valueParsed = true;
				try {
					valueItem = boost::lexical_cast<TValue>(*inputValueItem);
				}
				catch (boost::bad_lexical_cast const& exception) {
					valueParsed = false;
				}
				
				// fill output maps
				if (keyParsed)
				{
					if (valueParsed)
					{
						if (outputMap.count(key) == 0)
						{
							outputMap[key] = std::vector<TValue>();
						}
						outputMap[key].push_back(valueItem);
					}
					else
					{
						if (outputMapWrongTValue.count(key) == 0)
						{
							outputMapWrongTValue[key] = std::vector<std::string>();
						}
						outputMapWrongTValue[key].push_back(*inputValueItem);
					}
				}
				else
				{
					if (valueParsed)
					{
						if (outputMapWrongTKey.count(inputItem->first) == 0)
						{
							outputMapWrongTKey[inputItem->first] = std::vector<TValue>();
						}
						outputMapWrongTKey[inputItem->first].push_back(valueItem);
					}
					else
					{
						if (outputMapWrongTKeyWrongTValue.count(inputItem->first) == 0)
						{
							outputMapWrongTKeyWrongTValue[inputItem->first] = std::vector<std::string>();
						}
						outputMapWrongTKeyWrongTValue[inputItem->first].push_back(*inputValueItem);
					}
				}
			}
		}
		
		return outputMap;
	}
	
	template<class TKey, class TValue>
	std::map<TKey, std::vector<TValue> > ParseMapTypes(std::map<std::string, std::vector<std::string> > const& inputMap)
	{
		std::map<std::string, std::vector<TValue> > outputMapWrongTKey;
		std::map<TKey, std::vector<std::string> > outputMapWrongTValue;
		std::map<std::string, std::vector<std::string> > outputMapWrongTKeyWrongTValue;
		
		return ParseMapTypes(inputMap, outputMapWrongTKey, outputMapWrongTValue, outputMapWrongTKeyWrongTValue);
	}
	
	template<class TKey, class TValue>
	std::map<TKey, std::vector<TValue> > ParseMapTypes(std::map<std::string, std::vector<std::string> > const& inputMap,
	                                                   std::map<std::string, std::vector<TValue> > & outputMapWrongTKey)
	{
		std::map<TKey, std::vector<std::string> > outputMapWrongTValue;
		std::map<std::string, std::vector<std::string> > outputMapWrongTKeyWrongTValue;
		
		return ParseMapTypes(inputMap, outputMapWrongTKey, outputMapWrongTValue, outputMapWrongTKeyWrongTValue);
	}
	
	template<class TKey, class TValue>
	std::map<TKey, std::vector<TValue> > ParseMapTypes(std::map<std::string, std::vector<std::string> > const& inputMap,
	                                                   std::map<std::string, std::vector<TValue> > & outputMapWrongTKey,
	                                                   std::map<TKey, std::vector<std::string> > & outputMapWrongTValue)
	{
		std::map<std::string, std::vector<std::string> > outputMapWrongTKeyWrongTValue;
		
		return ParseMapTypes(inputMap, outputMapWrongTKey, outputMapWrongTValue, outputMapWrongTKeyWrongTValue);
	}
}

