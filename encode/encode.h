//
//  encode.h
//  langtons_ant
//
//  Created by Srinivas Dhanwada on 8/26/16.
//  Copyright © 2016 dhanwada. All rights reserved.
//

#ifndef encode_h
#define encode_h

#define NAME_TEMPLATE ".langton_data/%010u.pbm"

extern int _x_size, _y_size, _skip, _sequence_number;

int start_encode(int x_size, int y_size, int skip);
int next_frame(char *data);
int finish_encode(void);

#endif /* encode_h */
