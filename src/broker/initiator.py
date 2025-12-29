"""
This is a demo file to ensure that the exchange
can receive orders from a demo broker such as this 
file
"""
import quickfix as fix
import time
from datetime import datetime

SOH = chr(1)

class Application(fix.Application):
    sessionID = "BROKER1"
    cl_ord_id = int(time.time() * 1e6)

    # ---- session lifecycle ----
    def onCreate(self, sessionID):
        print("onCreate", sessionID)

    def onLogon(self, sessionID):
        self.sessionID = sessionID
        print("LOGON", sessionID)

    def onLogout(self, sessionID):
        print("LOGOUT", sessionID)

    # ---- admin ----
    def toAdmin(self, message, sessionID):
        print("ADMIN S >>", message.toString().replace(SOH, "|"))

    def fromAdmin(self, message, sessionID):
        print("ADMIN R <<", message.toString().replace(SOH, "|"))

    # ---- app ----
    def toApp(self, message, sessionID):
        print("APP   S >>", message.toString().replace(SOH, "|"))

    def fromApp(self, message, sessionID):
        print("APP   R <<", message.toString().replace(SOH, "|"))

    # ---- helpers ----
    def nextClOrdID(self):
        self.cl_ord_id += 1
        return str(self.cl_ord_id)

    def send_new_order(self):
        if not self.sessionID:
            print("Not logged on yet")
            return

        msg = fix.Message()
        header = msg.getHeader()
        header.setField(fix.MsgType(fix.MsgType_NewOrderSingle))  # 35=D

        msg.setField(fix.ClOrdID(self.nextClOrdID()))             # 11
        msg.setField(fix.Symbol("MSFT"))                          # 55
        msg.setField(fix.Side(fix.Side_BUY))                      # 54
        msg.setField(fix.OrderQty(100))                           # 38
        msg.setField(fix.OrdType(fix.OrdType_LIMIT))              # 40
        msg.setField(fix.Price(100.25))                           # 44
        msg.setField(fix.TimeInForce(fix.TimeInForce_DAY))        # 59

        tx_time = fix.TransactTime()
        tx_time.setString(datetime.utcnow().strftime("%Y%m%d-%H:%M:%S.%f")[:-3])
        msg.setField(tx_time)                                     # 60

        fix.Session.sendToTarget(msg, self.sessionID)


def main():
    settings = fix.SessionSettings("initiator.cfg")

    app = Application()
    store = fix.FileStoreFactory(settings)
    log = fix.FileLogFactory(settings)

    initiator = fix.SocketInitiator(app, store, settings, log)


    initiator.start()
    print("Initiator started")

    try:
        while True:
            cmd = input("1 = send order, q = quit: ")
            if cmd == "1":
                app.send_new_order()
            elif cmd == "q":
                break
    finally:
        initiator.stop()
        print("exit")

if __name__ == "__main__":
    main()
