
#include "MenuService.h"
#include <spc/spcbase.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>

#include "XmlAccessor.hpp"

namespace spc {
	// メインプロシージャ
	void MenuService::onInitialize(){
		
		setLogLevel(SPC_LOG_LEVEL_TRACE); 

    	SPC_LOG_DEBUG("*** start ***");
		
 		SPC_ANSWER answer;
 		std::vector<std::string> answerWords;
 		std::string recogWord;
 		int recogIndex;

 		// 認識したい言葉を全角カタカナで追加する
		// オイシイ、ウマイ、ウッマのいずれかを認識する
		answerWords.push_back("イイネ");
 		answerWords.push_back("ハイ");
 		answerWords.push_back("ソレニシヨウ");

 		// 質問をする
 		long rtn;
		
		std::string oldest_date;
		std::string main_menu_name;
		std::string sub_menu_names;
		oldest_date = "10";
		main_menu_name = "ボルシチ";
		sub_menu_names = "ハンバーグ、ラーメン、アイスクリーム、さいころステーキ、みそしる";
		//TODO: 最古の日にちとメニューの名称を取得してくる
		
 		rtn = waitForAnswer("いちばんむかしにつくったメニューで" + oldest_date + "にちまえに" + main_menu_name + "を作っていますが、今日あたりどうですか",
              answerWords,
              answer,
              recogWord,
              recogIndex);
 		if(rtn != 0){
   		// waitForAnswer処理失敗
   		// アプリケーションの終了
   		exitComponent();
   		return;
 		}
 		switch(answer){
   		case SPC_ANSWER_RECOGEND:
     		// ここに質問が正常終了した場合の処理を記述する
 	
 			speak("こんなおかずをいっしょにつくっていましたよ");
 			//TODO: 一番昔に作ったメニューに紐づくサブメニューを全て取得してくる(文字列として？)
 			speak(sub_menu_names);
 			
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
	}	
}
