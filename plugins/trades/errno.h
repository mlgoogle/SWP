//  Copyright (c) 2017-2018 The SWP Authors. All rights reserved.
//  Created on: 2017年2月12日 Author: kerry

#ifndef SWP_TRADES_ERRNO_H_
#define SWP_TRADES_ERRNO_H_

enum TRADESERRNO {
  FORMAT_ERRNO = -100,
  NO_HAVE_PLATFORM = -601,
  NO_HAVE_TRADES_GOODS = -602,
  NO_HAVE_QUOTATIONS_DATA = -603,
  NO_HAVE_CHARGE = -604,
  NO_HAVE_GOODS_DATA = -605
};

#endif
