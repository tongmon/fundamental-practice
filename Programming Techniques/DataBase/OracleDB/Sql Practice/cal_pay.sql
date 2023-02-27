SET VERIFY OFF
ACCEPT in_id PROMPT 'Enter id #: '
ACCEPT in_name PROMPT 'Enter name: '
ACCEPT in_hrs PROMPT 'Enter hours worked: '
ACCEPT in_payhr PROMPT 'Enter pay per hour: '
DECLARE
  v_pay NUMBER(6,2);
  v_hrs NUMBER(2) :=&in_hrs;
  v_payhr NUMBER(5,2) := &in_payhr;
BEGIN
  v_pay := v_hrs * v_payhr;
  INSERT INTO testpay
  VALUES(&in_id,'&in_name', v_pay);
END;
/
SET VERIFY ON
