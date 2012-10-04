//---------------------------------------------------------------------------
#include <vcl.h>
#include <map>
#pragma hdrstop
#include "FilePtr.h"
#include "Functions.h"

//---------------------------------------------------------------------------

#pragma argsused

class TPlayer {
public:
  const int Id;
  const String Country, Type, Name;
  __fastcall TPlayer(int I, const String &C, const String &T, const String &N) : Id(I), Country(C), Type(T), Name(N) {}
  void __fastcall Write(FILE *outp) const {
    fprintf(outp, "insert into t_player_buf(country, player_type, num, name) values('%s', '%s', %d, '%s');\n", Country, Type, Id, Name);
  }
};
typedef std::map<int, TPlayer> TPlayerList;
int main(int argc, char* argv[]) {
  try {
    if(argc<3) throw Exception("usage:\nPlayerParser mask output");
    TFilePtr outp(argv[2], "wt");
    ns_Functions::TFileList FileList;
    ns_Functions::GetFileList(FileList, argv[1]);
    String Country="", PlayerType="", Player="";
    for(ns_Functions::TFileIt i=FileList.begin(); i!=FileList.end(); ++i) {
      TPlayerList PlayerList;
      printf("%s\n", *i);
      Country = StringReplace(*i, "'", "''", TReplaceFlags()<<rfReplaceAll);
      TFilePtr inp(*i, "rt");
      char buf[1024];
      while(fgets(buf, 1024, inp)) {
//        printf(".");
        String Str=String(buf).Trim();
        if(Str.Length()<1) continue;
        int N=0;
        try {
          N = Str.ToInt();
          fgets(buf, 1024, inp);
          *strchr(buf, '\t')=0;
          Player = StringReplace(buf, "'", "''", TReplaceFlags()<<rfReplaceAll);
          fgets(buf, 1024, inp);
          fgets(buf, 1024, inp);
        } catch(...) {
          PlayerType = Str;
          printf("%s\n", PlayerType);
          continue;
        }
        PlayerList.insert(std::make_pair(N, TPlayer(N, Country, PlayerType, Player)));
        printf("%s, %s, %d, %s\n", *i, PlayerType, N, Player);
      }
      printf("\n");
      for(TPlayerList::const_iterator i=PlayerList.begin(); i!=PlayerList.end(); ++i) {
        i->second.Write(outp);
        printf("%2d %s\n", i->second.Id, i->second.Name);
      }
      printf("%u\n", PlayerList.size());
      fprintf(outp, "commit;\n");
    }
  }
  catch(Exception &E) {
    printf("%s", E.Message);
    return -1;
  }
  return 0;
}
//---------------------------------------------------------------------------
 