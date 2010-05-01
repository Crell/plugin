<?php

/*$ctx->get('og', 'current');

$ctx['current_og'];

$ctx->path();
$ctx->rawPath();
$ctx->language();
$ctx->og()->currentOg();

$ctx->currentOg();

$new_ctx = $ctx->mock(array(
  'currentOg' => 5,
));
*/

class Context {
  function __construct($overrides = array(), $inner = NULL) {
    $this->values = $overrides;
    $this->inner = $inner;
  }

  function get($foo) {
    if (!empty($this->values[$foo])) {
      if (isset($this->inner)) {
        return $this->inner->get($foo);
      }
      else {
        $this->values[$foo] = get_from_registered_responders();
      }
    }
    return $this->values[$foo];
  }

  function mock($overrides = array()) {
    return new self($overrides, $this);
  }
}

function get_from_registered_responders() {
  return 'a';
}

$c = new Context();
$m = $c->mock(array('primaryNode' => node_load(5)));

function hook_question() {
  $info['primaryNode'] = array();

  return $info;
}

function hook_answer() {
  $info['primaryNode'] = array(
    'handler' => 'PrimaryNode',
  );
  return $info;
}

