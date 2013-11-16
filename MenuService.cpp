
#include "MenuService.h"
#include <spc/spcbase.h>
#include <fstream>
#include <string>
#include <vector>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <iostream>
#include <sstream>

#include "Menus.hpp"

using namespace Model;

namespace spc {
	// メインプロシージャ
	void MenuService::onInitialize(){
		
		setLogLevel(SPC_LOG_LEVEL_TRACE); 

    	SPC_LOG_DEBUG("*** start ***");

		Menus menus; 
		
 		SPC_ANSWER answer;
 		std::vector<std::string> answerWords;
 		std::string recogWord;

		std::vector<std::string> yesWords, noWords, cancelWords;

 		// 認識したい言葉を全角カタカナで追加する
		// オイシイ、ウマイ、ウッマのいずれかを認識する
		yesWords.push_back("イイネ");
 		yesWords.push_back("ハイ");
 		yesWords.push_back("ソレニシヨウ");

		noWords.push_back("イヤデス");
		noWords.push_back("イヤ");
		noWords.push_back("ベツノモノニシタイ");
		noWords.push_back("ベツノモノガイイ");
		noWords.push_back("ホカノモノガイイ");
		cancelWords.clear();

		
 		// 質問をする
 		long rtn;

		std::string main_menu;
		std::string sub_menus;	
		int i;
		int k = 0;
		int max = menus.count_main_menu();

		for ( i=0; i<max; i=i+1 ){
			int j = 0;
			main_menu = menus.select_main_menu();
 			rtn = waitForAnswer(main_menu,
 			yesWords,
              noWords,
              cancelWords,
              answer);

			 switch(answer){
			 case SPC_ANSWER_YES:
			 		j = 1;
			 		break;
			 case SPC_ANSWER_NO:	
			 		break;			 	
			 }
			if(j == 1){
				break;
			}
			k++;

			if(k == max){
				speak("すみません。もう覚えている献立はありません。");
				break;
			}
			
        }

 		if(rtn != 0){
   		// waitForAnswer処理失敗
   		// アプリケーションの終了
   		exitComponent();
   		return;
 		}
 		switch(answer){
   		case SPC_ANSWER_YES:
     		// ここに質問が正常終了した場合の処理を記述する
 	
 			speak("こんなおかずをいっしょにつくっていましたよ");
 			sub_menus = menus.select_sub_menu(menus.id);  
 			speak(sub_menus);
 			speak("献立のヒントになりましたか？");
 			speak("料理頑張ってくださいね！");
 			
 			break;
   		case SPC_ANSWER_CANCEL:
     		// ここに「やめる」を認識した時の処理を記述する
 	
 	 		speak("やめました");
 	
     		break;

   		case SPC_ANSWER_TIMEOUT:
     		// ここに質問処理がタイムアウトした時の処理を記述する
 	
 	 		speak("返答が無かったので終了しました");
 	
     		break;

   		default:
     		break;
 		}
	exitComponent();
    return;
	}
}
