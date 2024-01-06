#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct record
{
  int red;
  int blue;
  int green;

  record(const int red_t, const int blue_t, const int green_t) : red(red_t), blue(blue_t), green(green_t)
  {
  }
};

const record valid_record(12, 13, 14);

bool IsRecordValid(const std::string &color, const int amount)
{
  if (color.empty() || amount <= 0)
  {
    return false;
  }

  if (color == "red")
  {
    return amount <= valid_record.red;
  }

  if (color == "blue")
  {
    return amount <= valid_record.blue;
  }

  if (color == "green")
  {
    return amount <= valid_record.green;
  }

  return false;
}

int main()
{
  int valid_games_count = 0;
  std::fstream input_file("in.txt");
  if (input_file.is_open())
  {
    std::string line;
    while (input_file)
    {
      std::getline(input_file, line);
      if (line.empty())
      {
        break;
      }

      std::stringstream ss;
      const std::size_t column_pos = line.find(":");
      if (column_pos == std::string::npos)
      {
        break;
      }

      const std::string id_str = line.substr(0, column_pos);
      const std::size_t id_pos = id_str.find(" ");
      const std::string id_num_str = id_str.substr(id_pos + 1);
      int id_num;
      ss << id_num_str;
      ss >> id_num;
      ss.str(std::string());

      bool is_game_valid = true;
      std::string games_str = line.substr(column_pos + 2);
      while (!games_str.empty() && is_game_valid)
      {
        const std::size_t separator_pos = games_str.find(";");
        if (separator_pos == std::string::npos)
        {
          break;
        }

        std::string game_str = games_str.substr(0, separator_pos);
        while (!game_str.empty() && is_game_valid)
        {
          const std::size_t comma_pos = game_str.find(",");
          if (comma_pos == std::string::npos)
          {
            break;
          }

          const std::string record_str = game_str.substr(0, comma_pos);
          const std::size_t space_pos = record_str.find(" ");
          const std::string amount_str = record_str.substr(0, space_pos);
          const std::string color_str = record_str.substr(space_pos + 1);
          int amount_num;
          ss << amount_str;
          ss >> amount_num;
          ss.str(std::string());

          if (!IsRecordValid(color_str, amount_num))
          {
            is_game_valid = false;
            break;
          }

          game_str = game_str.substr(comma_pos + 1);
        }

        games_str = games_str.substr(separator_pos + 1);
      }

      if (is_game_valid)
      {
        valid_games_count += id_num;
      }
    }
  }

  return 0;
}
