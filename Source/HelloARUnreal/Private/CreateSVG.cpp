// // Copyright 2017 Google Inc.//// Licensed under the Apache License, Version 2.0 (the "License");// you may not use this file except in compliance with the License.// You may obtain a copy of the License at//// http://www.apache.org/licenses/LICENSE-2.0//// Unless required by applicable law or agreed to in writing, software// distributed under the License is distributed on an "AS IS" BASIS,// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.// See the License for the specific language governing permissions and// limitations under the License.

#include "CreateSVG.h"
#include "CoreMinimal.h"
#include "Paths.h"
#include "FileHelper.h"
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <fstream>


bool UCreateSVG::FileSaveString(FString SaveTextB, FString FileNameB)
{
	return FFileHelper::SaveStringToFile(SaveTextB, *(FPaths::ProjectDir() + FileNameB));
}

bool UCreateSVG::FileLoadString(FString FileNameA, FString& SaveTextA)
{
	return FFileHelper::LoadFileToString(SaveTextA, *(FPaths::ProjectDir() + FileNameA));
}

// Called every frame
void UCreateSVG::CreateSVGFunction(FString& UploadStatus, FString FileName, FString objectStream)
{
	//auto client = Aws::MakeShared<DynamoDBClient>(ALLOCATION_TAG, AWSCredentials("AKIAJBGQOBEAF54WGFRQ", "TSDCBGpOluuIey8e6eSQaXmJ8g3x8/6bH/qR4EiM"), config);
	Aws::Client::ClientConfiguration clientConfig;

	clientConfig.region = "eu-west-1";
	Aws::S3::S3Client s3_client(clientConfig);

	Aws::S3::Model::PutObjectRequest object_request;
	object_request.WithBucket("https://s3-us-west-2.amazonaws.com/mobilikon-packages/").WithKey("AKIAJBGQOBEAF54WGFRQ");

	// Binary files 

	//const TCHAR* wavLink = *objectStream;
	//char* objectStreamChar = TCHAR_TO_ANSI(wavLink);
	auto input_data = Aws::MakeShared<Aws::FStream>("objectStream",
		"awdawdawd", std::ios_base::in | std::ios_base::binary);

	//UE_LOG(LogTemp, Warning, TEXT("Done! %s" ) objectStreamChar);
	object_request.SetBody(input_data);

	auto put_object_outcome = s3_client.PutObject(object_request);

	if (put_object_outcome.IsSuccess())
	{
		//done
		UploadStatus = "Done";
		UE_LOG(LogTemp, Warning, TEXT("Done!"));
	}
	else
	{
		UploadStatus = "Faild";
		UE_LOG(LogTemp, Warning, TEXT("Faild!"));
		//fucked up!
	}
//
	
}